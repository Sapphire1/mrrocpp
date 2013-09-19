/**
 * ib_eih_wrist_move.h
 *
 *  @date 2012
 * 	@author lzmuda
 */

#ifndef IB_EIH_WRIST_MOVE_H_
#define IB_EIH_WRIST_MOVE_H_

#include "visual_servo.h"
#include "IBReading.h"

namespace mrrocpp {

namespace ecp {

namespace servovision {


class ib_eih_wrist_move : public visual_servo
{
public:
	ib_eih_wrist_move(boost::shared_ptr <visual_servo_regulator> regulator, boost::shared_ptr <mrrocpp::ecp_mp::sensor::discode::discode_sensor> sensor, const std::string & section_name, mrrocpp::lib::configurator& configurator);
	virtual ~ib_eih_wrist_move();

	virtual Types::Mrrocpp_Proxy::IBReading* get_reading();
	virtual float get_ellipse_factor();
	virtual float get_objects_diameter();
	virtual void reset();
protected:
	virtual lib::Homog_matrix compute_position_change(const lib::Homog_matrix& current_position, double dt);
	virtual bool is_object_visible_in_latest_reading();
	virtual void retrieve_reading();
	virtual void predict_reading();

	lib::Homog_matrix e_T_c_position;
private:
	Eigen::Matrix <double, 4, 1> desired_position;
	Types::Mrrocpp_Proxy::IBReading reading;
};


}//namespace generator

}

}

#endif /* IB_EIH_WRIST_MOVE_H_ */
