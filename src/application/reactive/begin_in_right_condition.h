#ifndef BEGIN_IN_RIGHT_CONDITION_H_
#define BEGIN_IN_RIGHT_CONDITION_H_
#include "begin_condition.h"
#include <vector>
using namespace mrrocpp::ecp::common::generator;

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {


class begin_in_right_condition : public begin_condition
{	
private:
	std::vector<double> limitation;
public:
	begin_in_right_condition(){};
	begin_in_right_condition(std::vector<double>  & );
	~begin_in_right_condition(){};
	bool check(boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour> &);
};

} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp

#endif


