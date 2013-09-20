/*
* objectNotVisibleTerminate.cpp
*
* Created on: 18-09-2013
* Author: lzmuda
*/

#include "objectNotVisibleTerminate.h"
using namespace mrrocpp::ecp::common::generator;

namespace mrrocpp {
namespace ecp {
namespace condition {

objectNotVisibleTerminate::objectNotVisibleTerminate(const lib::configurator& config, const std::string &section_name) {

}

objectNotVisibleTerminate::~objectNotVisibleTerminate() {
}

bool objectNotVisibleTerminate::check(mrrocpp::ecp::common::generator::behaviour * bh1)
{
 	std::cout<<"objectNotVisibleTerminate::check\n";
	visual_behaviour *v_bhr = dynamic_cast<visual_behaviour *>(bh1);
	lib::Homog_matrix tmp;
	v_bhr->vs->get_sensor()->get_reading();
	v_bhr->vs->get_position_change(tmp, 0.1);
	float diameter = v_bhr->vs->get_objects_diameter();
	std::cout << "Srednica obiektu to :" << diameter<< "\n";
	if(diameter>0)
	{
		std::cout << "objectNotVisibleTerminate::check\n";
		std::cout<<"begin_visible_condition::check() end\n";
		return false;
	}
	else
	{
		std::cout << "Object is not visible\n";
		std::cout<<"objectNotVisibleTerminate::check end\n";
		return true;
	}
}

void objectNotVisibleTerminate::reset()
{

}

} /* namespace condition */
} /* namespace ecp */
} /* namespace mrrocpp */
