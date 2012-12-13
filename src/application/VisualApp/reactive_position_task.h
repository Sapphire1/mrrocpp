/**
  *  @file reactive_position_task.h
  *  @brief Create and run behaviours.
  *  @date 2012
  *  @author lzmuda
  */

#ifndef REACTIVE_POSITION_TASK_H
#define REACTIVE_POSITION_TASK_H

#include <boost/shared_ptr.hpp>
#include "reactive_task.h"
#include "robot/irp6p_m/ecp_r_irp6p_m.h"
#include "robot/irp6ot_m/ecp_r_irp6ot_m.h"

using namespace mrrocpp::ecp::common::generator;
using namespace mrrocpp::ecp::common::task;
using namespace mrrocpp::ecp::common::generator;
namespace mrrocpp {
namespace ecp {
namespace common {
namespace task {

class reactive_position_task : public reactive_task
{
public: 
      reactive_position_task(mrrocpp::lib::configurator & configurator);
      ~reactive_position_task(){};
};

}//namespace task
}
}
}
 
#endif /*  REACTIVE_POSITION_TASK  */
