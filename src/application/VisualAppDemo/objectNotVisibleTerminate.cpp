/*
 * objectNotVisibleTerminate.cpp
 *
 *  Created on: 18-09-2013
 *      Author: lzmuda
 */

#include "objectNotVisibleTerminate.h"
using namespace mrrocpp::ecp::common::generator;

namespace mrrocpp {
namespace ecp {
namespace condition {

objectNotVisibleTerminate::objectNotVisibleTerminate(const lib::configurator& config, const std::string &section_name) {

	  max_linear_speed = config.value <double> ("max_linear_speed", section_name);
	 max_angular_speed = config.value <double> ("max_angular_speed", section_name);
	  max_linear_accel = config.value <double> ("max_linear_accel", section_name);
	  max_angular_accel = config.value <double> ("max_angular_accel", section_name);
	  max_linear_error = config.value <double> ("max_linear_error", section_name);
	  max_angular_error = config.value <double> ("max_angular_error", section_name);
	  min_steps = config.value <int> ("min_steps", section_name);
	  steps_delay = 0;
}

objectNotVisibleTerminate::~objectNotVisibleTerminate() {
	std::cout<<"Destruktor\n";
}

bool objectNotVisibleTerminate::check(mrrocpp::ecp::common::generator::behaviour * bh1)
{/*

	visual_behaviour *v_bhr = dynamic_cast<visual_behaviour *>(bh1);
	v_bhr->vs->get_error();
	v_bhr->get_current_position();
	v_bhr->vs->is_object_visible();
	if (!(v_bhr->vs->is_object_visible()))
	{
		std::cout<<"Object is not visible!!!\n";
		v_bhr->vs->get_sensor()->terminate2();
		return true;
	}

	return false;
	*/
	std::cout<<"objectNotVisibleTerminate::check\n";
	visual_behaviour *v_bhr = dynamic_cast<visual_behaviour *>(bh1);
	bool object_visible_and_error_small = false;
	Eigen::Matrix <double, 6, 1> e = v_bhr->vs->get_error();
	Eigen::Matrix <double, 2, 1> linear_error = e.block(0, 0, 2, 1);
	Eigen::Matrix <double, 3, 1> angular_error = e.block(3, 0, 3, 1);
	//std::cout<<"linear_error : "<<linear_error <<std::endl;
	if (!(v_bhr->vs->is_object_visible()))
	{
		std::cout<<"Set object_not visible \n";
		object_visible_and_error_small = true;
	}

  if (object_visible_and_error_small) {
	  std::cout<<"Increment steps_delay\n";
	  steps_delay++;
	  std::cout<<"steps_delay "<<steps_delay<<"\n";
	  if (steps_delay >= 1) {
		  std::cout<<"objectNotVisibleTerminate-przekroczona liczba krokow...\n";
		  std::cout<<"Terminate VisualServo\n";
		  // to moze bedzie trzeba zmienic!!!
		  //v_bhr->vs->get_sensor()->terminate2();
		  return true;
	 }
  }



  std::cout<<"objectNotVisibleTerminate::check; end\n";
  return false;
}
void objectNotVisibleTerminate::reset()
{
	std::cout<<"reset counter\n";
	//steps_delay = 0;
}

} /* namespace condition */
} /* namespace ecp */
} /* namespace mrrocpp */
