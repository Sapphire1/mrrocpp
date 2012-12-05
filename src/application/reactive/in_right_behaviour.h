#if !defined(_IN_RIGHT_BEHAVIOUR_H)
#define _IN_RIGHT_BEHAVIOUR_H

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
//  in_left_behaviour
//  in_rigth_bahaviour
class in_right_behaviour : public common::generator::behaviour
{
public:
	/**
	 * @brief Constructor
	 * @param _ecp_task ecp task object referencex.
	 */
	in_right_behaviour(common::task::task& _ecp_task);
	~in_right_behaviour(){};

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
