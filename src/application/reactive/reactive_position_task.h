// /**
//  * reactive_position_task.h
//  *
//  *  Created on: 2012
//  *      Author: lzmuda
//  */
// 
#ifndef REACTIVE_POSITION_TASK
#define REACTIVE_POSITION_TASK

#include <boost/shared_ptr.hpp>
#include "../VisualApp/visual_servo_regulator_p.h"
// #include "position_behaviour.h"
#include "reactive_task.h"
#include "robot/irp6p_m/ecp_r_irp6p_m.h"
#include "robot/irp6ot_m/ecp_r_irp6ot_m.h"

using namespace mrrocpp::ecp::common::generator;
using namespace mrrocpp::ecp::common::task;

using namespace mrrocpp::ecp::servovision;
 using namespace mrrocpp::ecp::common::generator;
 namespace mrrocpp {
 
 namespace ecp {
 
 namespace common {
 
 namespace task {
 ///TODO
 /// zobaczyc jak to jest z generatorem i z taskiem i odpowiednio dopasowac; wywolywac od gory i testowac tak a nie od dolu
class reactive_position_task : public reactive_task
{
public: 
      reactive_position_task(mrrocpp::lib::configurator & configurator);
      ~reactive_position_task(){};
  	  boost::shared_ptr <visual_servo_regulator> reg;
};

 
 }//namespace task

}

}

}
 
#endif /*  REACTIVE_POSITION_TASK  */
