#ifndef TERMINATE_CONDITION_H_
#define TERMINATE_CONDITION_H_
#include "condition.h"


namespace mrrocpp {
namespace ecp {
namespace condition {
class terminate_condition : public condition
{
public:
	terminate_condition(){};
	virtual ~terminate_condition(){};
	/*!
		* @brief Method responsible for checking if condition can to be activated
		* @param pointer to behaviour
		*/
	virtual bool check(mrrocpp::ecp::common::generator::behaviour *)=0;
	virtual void reset()=0;
};


} // namespace condition

} // namespace ecp

} // namespace mrrocpp

#endif
