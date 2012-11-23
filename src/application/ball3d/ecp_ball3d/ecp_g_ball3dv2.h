#ifndef ECP_T_BALL3DV2_IB_H_
#define ECP_T_BALL3DV2_IB_H_
#include "base/ecp/ecp_task.h"
#include <boost/shared_ptr.hpp>
#include "../generator_ball3d/ecp_g_ball3d.h"

using namespace mrrocpp::ecp::common::generator;

namespace mrrocpp {

namespace ecp {

namespace common {

namespace task {

/** @addtogroup servovision
 *  @{
 */

/**
 *
 */
class ball3d: public mrrocpp::ecp::common::task::task
{
public:
	ball3d(mrrocpp::lib::configurator& configurator);

	void main_task_algorithm(void);

protected:

	void move_visual_servo();

	//shared_ptr<smooth> smooth_gen;
// 	shared_ptr<single_visual_servo_manager> sm;shared_ptr<single_visual_servo_manager> sm;
	generator::ball3d* b3d;
// 	shared_ptr<visual_servo_regulator> reg;
// 	shared_ptr<termination_condition> object_reached_term_cond;
// 	shared_ptr<termination_condition> timeout_term_cond;

// 	std::string vs_config_section_name;
};

/** @} */

}//namespace task

}

}

}


#endif