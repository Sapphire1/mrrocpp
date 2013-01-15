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
#include "visual_arm_behaviour.h"
#include "visual_wrist_behaviour.h"
#include "../VisualApp/ib_eih_visual_servo.h"
#include "../VisualApp/ib_eih_wrist_move.h"
#include "../VisualApp/visual_servo_regulator_p.h"
#include "object_reached_termination_condition.h"
#include "timeout_terminate_condition.h"
#include "terminate_in_left_condition.h"
#include "terminate_in_right_condition.h"
#include "beginvisiblecondition.h"
#include "begin_start_pos_condition.h"
#include "begin_behaviour.h"
using namespace mrrocpp::ecp::servovision;
//using namespace mrrocpp::ecp::condition;
namespace mrrocpp {
namespace ecp {
namespace condition {

boost::shared_ptr<terminate_condition> obj_reach_ter_cond;
}
}
}
namespace mrrocpp {
namespace ecp {

namespace common {

namespace task {

class reactive_visual_servo_task : public reactive_task
{
private:
	boost::shared_ptr<behaviour> start_beh;
	boost::shared_ptr<behaviour> arm_bh;
	boost::shared_ptr<behaviour> wrist_bh;
	boost::shared_ptr<visual_servo_regulator> reg_wrist;
	boost::shared_ptr<visual_servo_regulator> reg_arm;
	boost::shared_ptr<mrrocpp::ecp_mp::sensor::discode::discode_sensor> ds;
	boost::shared_ptr<mrrocpp::ecp_mp::sensor::discode::discode_sensor> ds_2;
	boost::shared_ptr<visual_servo> arm_vs;
	boost::shared_ptr<visual_servo> wrist_vs;

	boost::shared_ptr<terminate_condition> obj_reach_ter_cond;
	boost::shared_ptr<terminate_condition> time_ter_cond;
	boost::shared_ptr<terminate_condition> term_in_left;
	boost::shared_ptr<terminate_condition> term_beg_move;
	boost::shared_ptr<begin_condition> bgVisCond;
	boost::shared_ptr<begin_condition> bgStartPosCond;

public:
	reactive_visual_servo_task(mrrocpp::lib::configurator & configurator);
	virtual ~reactive_visual_servo_task();
};

}//task
}
}
}

#endif /* REACTIVEVISUALSERVOTASK_H_ */
