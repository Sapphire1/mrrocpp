#ifndef BEGIN_IN_LEFT_CONDITION_H_
#define BEGIN_IN_LEFT_CONDITION_H_
#include "begin_condition.h"
#include "in_left_behaviour.h"
#include <vector>
using namespace mrrocpp::ecp::common::generator;

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {


class begin_in_left_condition : public begin_condition
{	
private:
	std::vector<double> limitation;
public:
	begin_in_left_condition(){};
	begin_in_left_condition(std::vector<double>  &);
	~begin_in_left_condition(){};
	bool check(boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour> &);

};

} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp

#endif


