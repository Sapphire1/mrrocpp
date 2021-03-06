

/**
 *  @file ib_eih_wrist_move.cc
 *
 *  @date 2012
 *  @lzmuda
 */

#include "ib_eih_wrist_move.h"
#include "base/lib/logger.h"

#include <iostream>
#include <stdexcept>

using namespace logger;
using namespace std;
using namespace mrrocpp::ecp_mp::sensor::discode;

namespace mrrocpp {

namespace ecp {

namespace servovision {

ib_eih_wrist_move::ib_eih_wrist_move(boost::shared_ptr <visual_servo_regulator> regulator, boost::shared_ptr <
                mrrocpp::ecp_mp::sensor::discode::discode_sensor> sensor, const std::string & section_name, mrrocpp::lib::configurator& configurator) :
        visual_servo(regulator, sensor, section_name, configurator)
{
        desired_position = configurator.value <4, 1> ("desired_position", section_name);

        Eigen::Matrix <double, 3, 4> e_T_c;
        e_T_c.setZero();
        e_T_c.block(0,0,3,3) = configurator.value <3, 3> ("e_t_c_rotation", section_name);
        e_T_c_position = lib::Homog_matrix(e_T_c);
}

ib_eih_wrist_move::~ib_eih_wrist_move()
{
}

lib::Homog_matrix ib_eih_wrist_move::compute_position_change(const lib::Homog_matrix& current_position, double dt)
{
        log_dbg("wrist::ib_eih_visual_servo::compute_position_change() begin\n");

        lib::K_vector u_translation(0, 0, 0);
        lib::Homog_matrix u_rotation;
        Eigen::Matrix <double, 6, 1> e;


        e.setZero();

        Eigen::Matrix <double, Types::ImagePosition::elementsSize, 1> imagePosition(reading.imagePosition.elements);
        e.block(0, 0, 4, 1) = imagePosition - desired_position;

    	log_dbg("reading.imagePosition.elements = [%g; %g; %g; %g]\n", reading.imagePosition.elements[0], reading.imagePosition.elements[1], reading.imagePosition.elements[2], reading.imagePosition.elements[3]);

        error = e;

        Eigen::Matrix <double, 6, 1> control;
        // poruszanie manipulatorem w bok
       // e(2,0)=tool_vector[1]-1.7;
        control = regulator->compute_control(e, dt);
        log_dbg("ib_eih_visual_servo::get_position_change() control: [%+07.3lg; %+07.3lg; %+07.3lg; %+07.3lg]\n", control(0, 0), control(1, 0), control(2, 0), control(3, 0));

        Eigen::Matrix <double, 3, 1> camera_to_object_translation;
        camera_to_object_translation(0, 0) = -0.005;//control(2, 0)/5;
        camera_to_object_translation(1, 0) = 0;//control(1, 0);
        camera_to_object_translation(2, 0) = 0;//control(2, 0);
        u_translation = e_T_c_position * camera_to_object_translation;
        log_dbg("ib_eih_visual_servo::wrist::get_position_change() u_translation: %+07.3lg, %+07.3lg, %+07.3lg\n", u_translation(0, 0), u_translation(1, 0), u_translation(2, 0));
        // jak mam uchyb w x to sterowanie mam miec dla az
        u_rotation.set_from_xyz_angle_axis(lib::Xyz_Angle_Axis_vector(0, 0, 0, -2*control(1, 0), 3*control(0, 0), 0));
        lib::Homog_matrix delta_position;
        delta_position.set_rotation_matrix(u_rotation);
        delta_position.set_translation_vector(u_translation);
        log_dbg("wrist::ib_eih_visual_servo::compute_position_change() end\n");
        return delta_position;
}

float ib_eih_wrist_move::get_ellipse_factor(){
	Eigen::Matrix <double, Types::ImagePosition::elementsSize, 1> imagePosition(reading.imagePosition.elements);
	return reading.imagePosition.elements[3];
}

float ib_eih_wrist_move::get_objects_diameter(){
	Eigen::Matrix <double, Types::ImagePosition::elementsSize, 1> imagePosition(reading.imagePosition.elements);
	return reading.imagePosition.elements[2];
}

void ib_eih_wrist_move::retrieve_reading()
{
        try {
                 log_dbg("pb_visual_servo::retrieve_reading()\n");
                if (sensor->get_state() == discode_sensor::DSS_READING_RECEIVED) {
                                              log_dbg("pb_visual_servo::retrieve_reading(): sensor->get_state() == discode_sensor::DSS_READING_RECEIVED.\n");
                        reading = sensor->retreive_reading <Types::Mrrocpp_Proxy::IBReading> ();
                }
        } catch (exception &ex) {
                log("pb_visual_servo::retrieve_reading(): %s\n", ex.what());
        }
}

void ib_eih_wrist_move::predict_reading()
{

}
bool ib_eih_wrist_move::is_object_visible_in_latest_reading()
{
	std::cout<<"wrist::ib_eih_visual_servo::is_object_visible_in_latest_reading";

	if(reading.imagePosition.elements[2]==0)
		std::cout<<"\nwrist::Obiekt jest niewidoczny\n";
	else
		std::cout<<"\nObiekt jest widoczny\n";
	std::cout<<"ib_eih_visual_servo::is_object_visible_in_latest_reading end";
	return reading.imagePosition.elements[2]>0;
	//return reading.objectVisible;
}

Types::Mrrocpp_Proxy::IBReading* ib_eih_wrist_move::get_reading()
{
	std::cout<<"ib_eih_wrist_move::get_reading\n";
	std::cout<<reading.imagePosition.elements[2];
    return &reading;
}

void ib_eih_wrist_move::reset()
{
	std::cout<<"Reset widocznosci\n";
    visual_servo::reset();
    reading.objectVisible = false;
}

}//namespace generator
}
}

