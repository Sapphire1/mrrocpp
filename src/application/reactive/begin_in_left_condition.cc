#include "begin_in_left_condition.h"
#include "behaviour.h"
namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {


begin_in_left_condition::begin_in_left_condition(std::vector<double>  & a)
{
  limitation=a;
}


bool  begin_in_left_condition::check(mrrocpp::ecp::common::generator::behaviour* bh)
{

  return true;
  
}


} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp
