#ifndef TERMINATE_IN_RIGHT_CONDITION_H_
#define TERMINATE_IN_RIGHT_CONDITION_H_
#include "terminate_condition.h"

using namespace mrrocpp::ecp::common::generator;

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {


class terminate_in_right_condition : public terminate_condition
{
private:
	double limit;
public:
	terminate_in_right_condition(){};
	terminate_in_right_condition(double lim){limit=lim;};
	~terminate_in_right_condition(){};
	bool check(const boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour>&);
 	bool check(const mrrocpp::ecp::common::generator::behaviour &)const;
};


} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp

#endif 
