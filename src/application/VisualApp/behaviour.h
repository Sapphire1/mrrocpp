/*!
 * @file behaviour.h
 * @brief File containing the declaration of abstract common::generator::generator::behaviour class
 * @author lzmuda
 * date 2012
 */

#ifndef BEHAVIOUR_H_
#define BEHAVIOUR_H_
#include "base/ecp/ecp_generator.h"
#include "base/lib/mrmath/mrmath.h"
#include "base/lib/logger_client/logger_client.h"
#include "begin_condition.h"
#include "terminate_condition.h"
#include <vector>

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {

using logger::logger_client;
using logger::log_message;
using std::vector;

class behaviour : public common::generator::generator
{
public:
		/*!
		 * @brief Constructor.
		 *
		 * @param ecp_task
		 */
		behaviour(common::task::task& _ecp_task);
		/*!
		* @brief virtual destructor.
		*/
		virtual ~behaviour(){};
		/*!
		* @brief Method responsible for execute methods: fist_step and next_step.
		*
		* In that method are checked termination conditions.
		*/
		void Move();
		/*!
		* @brief Adding initial conditions to the behaviour object.
		*
		* @param begin_condition
		*/
		void add_begin_condition(boost::shared_ptr <begin_condition> &);
		/*!
		* @brief Adding terminate conditions to the behaviour object.
		*
		* @param terminate_condition
		*/
		void add_terminate_condition(boost::shared_ptr <terminate_condition> &);
		//!vector containing shared pointers to object begin_condition
		std::vector<boost::shared_ptr <begin_condition>> begin_conditions;
		//!vector containing shared pointers to object terminate_condition
		std::vector<boost::shared_ptr <terminate_condition>> terminate_conditions;
};


} // namespace generator	
} // namespace common
} // namespace ecp
} // namespace mrrocpp



#endif
