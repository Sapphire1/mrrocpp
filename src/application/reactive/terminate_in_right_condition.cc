#include "terminate_in_right_condition.h" 
#include "behaviour.h"
#include "base/ecp/ecp_robot.h"
#include "base/ecp/ecp_generator.h"

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {
  
bool terminate_in_right_condition::check(const boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour>& bh)
{

	return true;
}
bool terminate_in_right_condition::check(const mrrocpp::ecp::common::generator::behaviour& bh)const
{
	std::cout<<"terminate_in_right_condition::check()\n";
	lib::Homog_matrix tmp;
 	double current_position[6];
	lib::Xyz_Angle_Axis_vector tool_vector;
  	tmp=bh.the_robot->reply_package.arm.pf_def.arm_frame;
 	tmp.get_xyz_angle_axis(tool_vector);
 	tool_vector.to_table(current_position);
 	if(current_position[1]>=2.2)
 	{
		std::cout<<"Terminate Condition!!!\n";
 		return false;
 	}
	return true;
}
} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp