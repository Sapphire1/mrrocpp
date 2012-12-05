#include "begin_in_right_condition.h"
#include "behaviour.h"
namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {


begin_in_right_condition::begin_in_right_condition(std::vector<double>  & a)
{
  limitation=a;
}
// ta do wyrzucenia
bool begin_in_right_condition::check(const boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour> & bh)
{
      return true;
}

bool  begin_in_right_condition::check(const mrrocpp::ecp::common::generator::behaviour& bh)const
{

  return true;
  
}
// ta bedzie wykorzystywana


} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp