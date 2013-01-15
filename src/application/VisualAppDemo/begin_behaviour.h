#if !defined(_BEGIN_BEHAVIOUR_H)
#define _BEGIN_BEHAVIOUR_H

/*!
 * @file
 * @brief 
 * @author 
 *
 *
 * @ingroup generators
 */

#include "../VisualApp/behaviour.h"
#include "../VisualApp/visual_servo_regulator_p.h"
#include <Eigen/Core>
#include <math.h>
using namespace mrrocpp::ecp::servovision;
namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {


/*!
 * @brief 
 *
 * @author
 * @ingroup generators
 */

class begin_behaviour : public common::generator::behaviour
{
public:
	/**
	 * @brief Constructor
	 * @param _ecp_task ecp task object referencex.
	 */
	bool arm_stop;
	Eigen::Matrix <double, 6, 1> error;
	Eigen::Matrix <double, 6, 1> control;
	Eigen::Matrix <double, 6, 1> actual_position;
	boost::shared_ptr <visual_servo_regulator> reg;
	begin_behaviour(common::task::task& _ecp_task);
	~begin_behaviour(){};
	int counter;
	bool arm_set;
	bool wrist_set;
	/**
	 * @brief generates first step of transition function
	 * @return 
	 */
	bool first_step();
	bool next_step();
};

} // namespace generator
} // namespace common
} // namespace ecp
} // namespace mrrocpp



#endif
