/**
 *  @file visual_wrist_behaviour.cc
 *  @date 2013
 *  @author lzmuda
 */


#include <algorithm>

#include "base/ecp/ecp_task.h"
#include "base/ecp/ecp_robot.h"

#include "visual_wrist_behaviour.h"



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


visual_wrist_behaviour::visual_wrist_behaviour(mrrocpp::ecp::common::task::task & ecp_task, const char * section_name, boost::shared_ptr<logger::logger_client> & log_client,
		boost::shared_ptr <mrrocpp::ecp::servovision::visual_servo> wrist_vs)
: common::generator::visual_behaviour(ecp_task, section_name)
{
   this->log_client=log_client;
   this->vs=wrist_vs;
}
visual_wrist_behaviour::~visual_wrist_behaviour()
{

}

} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp
