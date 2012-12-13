/*!
 * @file condition.h
 * @brief File containing the declaration of switch_task class
 * 
 * @author Lukasz Zmuda
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
	* @brief Check if condition can to be activated
	*/
	virtual bool check(mrrocpp::ecp::common::generator::behaviour *)=0;
};

} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp

#endif