#include "terminate_in_left_condition.h" 
#include "behaviour.h"
#include "base/ecp/ecp_robot.h"
#include "base/ecp/ecp_generator.h"

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {
  
bool terminate_in_left_condition::check(mrrocpp::ecp::common::generator::behaviour* bh)
{
	std::cout<<"terminate_position_condition::check()\n";
	lib::Homog_matrix tmp;
 	double current_position[6];
	lib::Xyz_Angle_Axis_vector tool_vector;
  	tmp=bh->the_robot->reply_package.arm.pf_def.arm_frame;
 	tmp.get_xyz_angle_axis(tool_vector);
 	tool_vector.to_table(current_position);
 	if(current_position[1]<=1.8)
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