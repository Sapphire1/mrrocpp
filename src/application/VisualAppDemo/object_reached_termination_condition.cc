/*
 * object_reached_termination_condition.cc
 *
 *  Created on: Apr 29, 2010
 *      Author: mboryn
 */

#include "object_reached_termination_condition.h"
#include "base/lib/logger.h"

using namespace logger;

namespace mrrocpp {

namespace ecp {

namespace common {

namespace generator {

object_reached_termination_condition::object_reached_termination_condition(const lib::configurator& config, const std::string &section_name)
{
 	max_linear_speed = config.value <double> ("max_linear_speed", section_name);
	max_angular_speed = config.value <double> ("max_angular_speed", section_name);
 	max_linear_accel = config.value <double> ("max_linear_accel", section_name);
 	max_angular_accel = config.value <double> ("max_angular_accel", section_name);
 	max_linear_error = config.value <double> ("max_linear_error", section_name);
 	max_angular_error = config.value <double> ("max_angular_error", section_name);
 	min_steps = config.value <int> ("min_steps", section_name);
 	steps_delay = 0;
}

object_reached_termination_condition::~object_reached_termination_condition()
{
	reset();
}

void object_reached_termination_condition::reset()
{
	steps_delay = 0;
}
// no jak dla mnie to tutaj musi być szablon i tyle

bool object_reached_termination_condition::check(mrrocpp::ecp::common::generator::behaviour * bh1)
{
	visual_behaviour *v_bhr = dynamic_cast<visual_behaviour *>(bh1);
 	bool object_visible_and_error_small = false;

 		Eigen::Matrix <double, 6, 1> e = v_bhr->vs->get_error();
 		Eigen::Matrix <double, 3, 1> linear_error = e.block(0, 0, 3, 1);
 		Eigen::Matrix <double, 3, 1> angular_error = e.block(3, 0, 3, 1);

 		if (v_bhr->vs->is_object_visible() && linear_error.norm() <= max_linear_error
 				&& angular_error.norm() <= max_angular_error) {
 			object_visible_and_error_small = true;
 		}

 	if (object_visible_and_error_small && v_bhr->get_linear_speed() <= max_linear_speed && v_bhr->get_angular_speed()
 			<= max_angular_speed && v_bhr->get_linear_acceleration() <= max_linear_accel
 			&& v_bhr->get_angular_acceleration() <= max_angular_accel) {
 		steps_delay++;
 		if (steps_delay >= min_steps) {
 			position = v_bhr->get_current_position();
 			std::cout<<"Object reached terminate condition-przekroczona liczba krokow?\n";
 			return true;
 			//return false;
 		}
 	} else {
 		steps_delay = 0;

 	}
 	return false;
}

lib::Homog_matrix object_reached_termination_condition::get_position() const
{
	return position;
}



}//namespace generator

}

}

}
