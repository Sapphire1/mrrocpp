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

#include "behaviour.h"

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
	begin_behaviour(common::task::task& _ecp_task);
	~begin_behaviour(){};
	int counter;
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
