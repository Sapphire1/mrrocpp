/**
 *  @file terminate_in_left_condition.h
 *  @date 2012
 *  @author lzmuda
 */

#ifndef TERMINATE_IN_LEFT_CONDITION_H_
#define TERMINATE_IN_LEFT_CONDITION_H_
#include "application/VisualApp/terminate_condition.h"
#include "application/VisualApp/behaviour.h"
using namespace mrrocpp::ecp::common::generator;

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {


class terminate_in_left_condition: public terminate_condition
{
private:
	double limit;
public:
	terminate_in_left_condition();
	terminate_in_left_condition(double lim){limit=lim;};
	~terminate_in_left_condition(){};
 	bool check(mrrocpp::ecp::common::generator::behaviour *);
 	void reset();
};


} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp

#endif 
