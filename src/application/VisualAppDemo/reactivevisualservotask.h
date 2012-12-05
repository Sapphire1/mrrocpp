/*
 * reactivevisualservotask.h
 *
 *  Created on: Dec 3, 2012
 *      Author: sapphire
 */

#ifndef REACTIVEVISUALSERVOTASK_H_
#define REACTIVEVISUALSERVOTASK_H_

#include "robot/irp6p_m/ecp_r_irp6p_m.h"
#include "robot/irp6ot_m/ecp_r_irp6ot_m.h"
#include "../VisualApp/reactive_task.h"
#include "visual_behaviour.h"
#include "../VisualApp/ib_eih_visual_servo.h"
#include "../VisualApp/visual_servo_regulator_p.h"
#include "object_reached_termination_condition.h"
#include "timeout_terminate_condition.h"
#include "beginvisiblecondition.h"
using namespace mrrocpp::ecp::servovision;
namespace mrrocpp {

namespace ecp {

namespace common {

namespace task {

class reactive_visual_servo_task : public reactive_task
{
private:
	visual_behaviour* v_bhr;
	boost::shared_ptr<visual_servo_regulator> reg;
	boost::shared_ptr<mrrocpp::ecp_mp::sensor::discode::discode_sensor> ds;
	boost::shared_ptr<visual_servo> vs;
	boost::shared_ptr<terminate_condition> obj_reach_ter_cond;
	boost::shared_ptr<terminate_condition> time_ter_cond;
	boost::shared_ptr<begin_condition> bgVisCond;
public:
	reactive_visual_servo_task(mrrocpp::lib::configurator & configurator);
	virtual ~reactive_visual_servo_task();
};

}//task
}
}
}

#endif /* REACTIVEVISUALSERVOTASK_H_ */
