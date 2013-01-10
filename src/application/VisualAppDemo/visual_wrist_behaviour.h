/**
 *  @file visual_wrist_behaviour.h
 *  @date 2013
 *  @author lzmuda
 */


#ifndef VISUAL_WRIST_BEHAVIOUR_H_
#define VISUAL_WRIST_BEHAVIOUR_H_

#include <vector>
#include <boost/shared_ptr.hpp>
#include <string>

#include "base/ecp/ecp_generator.h"
#include "application/VisualApp/visual_servo.h"
#include "application/VisualAppDemo/visual_behaviour.h"
#include "application/VisualApp/position_constraint.h"
#include "application/VisualApp/terminate_condition.h"
#include "base/lib/logger_client/logger_client.h"
#include "application/VisualApp/behaviour.h"
#include "application/VisualApp/visual_servo_regulator_p.h"
#include "application/VisualApp/visual_servo.h"
#include <csignal>
#include <ctime>
#include <sstream>

namespace mrrocpp {

namespace ecp {

namespace servovision {
class termination_condition;
}

namespace common {

namespace generator {

/** @defgroup servovision Visual servoing
* @ingroup application
* @{
*/

/**
* Base generator for all visual servo managers.
* Servo manager is a generator that takes control calculated in multiple visual_servo objects and aggregates them.
* It also applies constraints for end effector speed, acceleration and position.
*/
class visual_wrist_behaviour: public visual_behaviour
{
public: 


visual_wrist_behaviour(mrrocpp::ecp::common::task::task & ecp_task, const char * section_name);
~visual_wrist_behaviour();
};

/** @} */

} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp

#endif /* VISUAL_SERVO_MANAGER_H_ */
