/*!
 * @file condition.h
 * @brief File containing the declaration of condition class
 * @author lzmuda
 * @date 2012
 */

#ifndef CONDITION_H_
#define CONDITION_H_
#include "base/ecp/ecp_generator.h"
using namespace mrrocpp::ecp::common::generator;
namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {

class behaviour;

/*!
 * @brief virtual class from which inheriting classes: begin_condition and terminate_condition
 */

class condition
{	
public:
	/*!
	* @brief Constructor
	*/
	condition(){};
	/*!
	* @brief Destructor
	*/
	virtual ~condition(){};
	
	/*!
	* @brief Method responsible for checking if condition can to be activated
	* @param pointer to behaviour
	*/
	virtual bool check(mrrocpp::ecp::common::generator::behaviour *)=0;
	/*!
	* @brief Reset condition
	*/
	virtual void reset() = 0;
};

} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp

#endif
