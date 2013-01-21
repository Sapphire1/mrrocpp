/**
 *  @file visual_arm_behaviour.cc
 *  @date 2013
 *  @author lzmuda
 */


#include <algorithm>

#include "base/ecp/ecp_task.h"
#include "base/ecp/ecp_robot.h"

#include "visual_arm_behaviour.h"



#include "../VisualApp/ib_eih_visual_servo.h"
#include "../VisualApp/ib_eih_wrist_move.h"


using namespace logger;
using namespace mrrocpp::ecp::servovision;
using namespace std;
using namespace mrrocpp::ecp::condition;


namespace mrrocpp {

namespace ecp {

namespace common {

namespace generator {



visual_arm_behaviour::visual_arm_behaviour(mrrocpp::ecp::common::task::task & ecp_task, const char * section_name, boost::shared_ptr<logger::logger_client> & log_client)
: common::generator::visual_behaviour(ecp_task, section_name)
{
  this->log_client=log_client;
  char config_section_name[] = { "[object_follower_ib]" };
  char config_section_name_arm[] = { "[servovision_arm]" };

  reg = boost::shared_ptr <visual_servo_regulator> (new regulator_p(ecp_task.config, config_section_name_arm));
  ds = boost::shared_ptr <mrrocpp::ecp_mp::sensor::discode::discode_sensor>(new mrrocpp::ecp_mp::sensor::discode::discode_sensor(ecp_task.config, config_section_name));
  vs = boost::shared_ptr <visual_servo> (new ib_eih_visual_servo(reg, ds, config_section_name, ecp_task.config));
  //! configuration of sensor if state is equal DSS_NOT_CONNECTED (0)
  configure();

}
visual_arm_behaviour::~visual_arm_behaviour()
{

}

} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp
