/**
 *  @file terminate_beg_pos_condition.h
 *  @date 2013
 *  @author lzmuda
 */

#ifndef TERMINATE_IN_RIGHT_CONDITION_H_
#define TERMINATE_IN_RIGHT_CONDITION_H_
#include "application/VisualApp/terminate_condition.h"
#include "application/VisualApp/behaviour.h"
#include <Eigen/Core>
using namespace mrrocpp::ecp::common::generator;

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {


class terminate_beg_pos_condition: public terminate_condition
{
private:
	double limit;
public:
	terminate_beg_pos_condition();
	terminate_beg_pos_condition(double lim){limit=lim;};
	~terminate_beg_pos_condition(){};
 	bool check(mrrocpp::ecp::common::generator::behaviour *);
 	void reset();
 	Eigen::Matrix <double, 6, 1> actual_position;
};


} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp

#endif 
