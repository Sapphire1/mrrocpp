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
#include "base/lib/mrmath/mrmath.h"

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {


/*!
 * @brief class for begin conditions 
 */


class begin_condition : public condition
{
public:
 	begin_condition(){};
	virtual ~begin_condition(){};
	/*!
		* @brief Method responsible for checking if condition can to be activated
		* @param reference to behaviour
		*/
	virtual bool check(boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour> &)=0;

};

} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp

#endif

