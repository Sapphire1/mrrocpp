#ifndef TERMINATE_CONDITION_H_
#define TERMINATE_CONDITION_H_
#include "condition.h"

using namespace mrrocpp::ecp::common::generator;
namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {

  
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
};


} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp
#endif
