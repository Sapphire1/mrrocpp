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



visual_arm_behaviour::visual_arm_behaviour(mrrocpp::ecp::common::task::task & ecp_task, const char * section_name, boost::shared_ptr<logger::logger_client> & log_client,
			boost::shared_ptr <mrrocpp::ecp::servovision::visual_servo> ib_eih_vs)
: common::generator::visual_behaviour(ecp_task, section_name)
{
  this->vs=ib_eih_vs;
  this->log_client=log_client;
}
visual_arm_behaviour::~visual_arm_behaviour()
{

}

} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp
