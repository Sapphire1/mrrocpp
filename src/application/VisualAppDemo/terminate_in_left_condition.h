/**
 *  @file terminate_in_left_condition.h
 *  @date 2012
 *  @author lzmuda
 */

#ifndef TERMINATE_IN_LEFT_CONDITION_H_
#define TERMINATE_IN_LEFT_CONDITION_H_
#include "application/VisualApp/terminate_condition.h"
#include "application/VisualApp/behaviour.h"
#include "application/VisualAppDemo/visual_behaviour.h"
using namespace mrrocpp::ecp::common::generator;

namespace mrrocpp {
namespace ecp {
namespace condition {


class terminate_in_left_condition: public terminate_condition
{
private:
	double limit;
	int counter;
public:
	terminate_in_left_condition()
	{
		counter=0;
	}
	terminate_in_left_condition(double lim){limit=lim;counter=0;}
	~terminate_in_left_condition(){counter=0;}
 	bool check(mrrocpp::ecp::common::generator::behaviour *);
 	void reset();
};

} // namespace condition

} // namespace ecp

} // namespace mrrocpp

#endif 
