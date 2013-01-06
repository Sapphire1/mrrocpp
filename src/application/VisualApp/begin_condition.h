/*!
 * @file condition.h
 * @brief File containing the declaration of begin_condition class
 * 
 * @author Lukasz Zmuda
 * @date 2012
 */


#ifndef BEGIN_CONDITION_H_
#define BEGIN_CONDITION_H_
#include "condition.h"
#include "behaviour.h"
#include "base/lib/mrmath/mrmath.h"

/*!
 * @brief class for begin conditions
 */
namespace mrrocpp {
namespace ecp {
namespace condition {
class condition;
class begin_condition : public condition
{
public:
	begin_condition(){};
	virtual ~begin_condition(){};
	/*!
		* @brief Method responsible for checking if condition can to be activated
		* @param pointer to behaviour
		*/
	virtual bool check(const boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour> &)=0;
	virtual void reset()=0;
};

} // namespace condition

} // namespace ecp

} // namespace mrrocpp


#endif

