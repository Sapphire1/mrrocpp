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
/*
max_linear_speed = config.value <double> ("max_linear_speed", section_name);
max_angular_speed = config.value <double> ("max_angular_speed", section_name);
max_linear_accel = config.value <double> ("max_linear_accel", section_name);
max_angular_accel = config.value <double> ("max_angular_accel", section_name);
max_linear_error = config.value <double> ("max_linear_error", section_name);
max_angular_error = config.value <double> ("max_angular_error", section_name);
min_steps = config.value <int> ("min_steps", section_name);
steps_delay = 0;
*/
}

objectNotVisibleTerminate::~objectNotVisibleTerminate() {
}

bool objectNotVisibleTerminate::check(mrrocpp::ecp::common::generator::behaviour * bh1)
{
visual_behaviour *v_bhr = dynamic_cast<visual_behaviour *>(bh1);
bool objectVisible = v_bhr->vs->is_object_visible();
// if(!objectVisible)
// v_bhr->vs->get_sensor()->terminate2();
if(!objectVisible)
std::cout<<"Object is not visible\n";
else
std::cout<<"Object is visible\n";
    return !objectVisible;
}
void objectNotVisibleTerminate::reset()
{

}

} /* namespace condition */
} /* namespace ecp */
} /* namespace mrrocpp */
