/*
* begin_condition_right.cpp
*
* Created on: Dec 4, 2012
* Author: lzmuda
*/

#include "begin_condition_right.h"
#include "application/VisualApp/behaviour.h"


namespace mrrocpp {
namespace ecp {
namespace condition {

begin_condition_right::begin_condition_right()
{

}

begin_condition_right::~begin_condition_right()
{
}

bool begin_condition_right::check(const boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour> & bhvr)
{
	lib::Homog_matrix actual_position_matrix;
	lib::Xyz_Angle_Axis_vector tool_vector;
	lib::Xyz_Angle_Axis_vector angle_axis_vector;
	std::vector<double> current_position(6);
	bhvr->the_robot->ecp_command.instruction_type = lib::GET;
	bhvr->the_robot->ecp_command.get_type = ARM_DEFINITION;

	// te dwie linie umozliwiaja odczytanie aktualnej pozycji
	bhvr->initiate_sensors_readings();
	bhvr->execute_motion();

	actual_position_matrix = bhvr->the_robot->reply_package.arm.pf_def.arm_frame;
	actual_position_matrix.get_xyz_angle_axis(angle_axis_vector);
	angle_axis_vector.to_vector(current_position);
	std::cout << "begin_condition_right::check : \n" << current_position[0]<<"\t"<<
	current_position[1]<<"\t\t"<< current_position[2]<<"\n"<< current_position[3]<<"\t\t"<<
	current_position[4]<<"\t"<< current_position[5]<<"\n";
	boost::shared_ptr<visual_behaviour> bh = boost::dynamic_pointer_cast<visual_behaviour>(bhvr);
	if(!bh->sensor_configured)
	{
	  std::cout<<"Konfiguracja sensora\n";
	  bh->configure();
	  bh->sensor_configured=true;
	}
	lib::Homog_matrix tmp;
	bh->vs->get_sensor()->get_reading();
	bh->vs->get_position_change(tmp, 0.1);

	float diameter = bh->vs->get_objects_diameter();
	std::cout << "Srednica obiektu to :" << diameter<< "\n";

	if(diameter>0 && current_position[1]<=1.8)
	{
		std::cout<<"Begin Condition in left is not met!!!\n";
		return false;
	}
	std::cout<<"Begin Condition in left is met!!!\n";
	return true;
	};

} /* namespace condition */
} /* namespace ecp */
} /* namespace mrrocpp */
