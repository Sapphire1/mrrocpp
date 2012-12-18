#include "terminate_in_right_condition.h"
#include "base/ecp/ecp_robot.h"
#include "base/ecp/ecp_generator.h"

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {
  
bool terminate_in_right_condition::check(mrrocpp::ecp::common::generator::behaviour* bh)
{
	std::cout<<"terminate_position_condition_right::check()\n";
	lib::Homog_matrix tmp;
 	double current_position[6];
	lib::Xyz_Angle_Axis_vector tool_vector;
  	tmp=bh->the_robot->reply_package.arm.pf_def.arm_frame;
 	tmp.get_xyz_angle_axis(tool_vector);
 	tool_vector.to_table(current_position);
 			  std::cout << current_position[0]<<"\t"<<
 			  current_position[1]<<"\t"<<
 			  current_position[2]<<"\n"<<
 			  current_position[3]<<"\t"<<
 			  current_position[4]<<"\t"<<
 			  current_position[5]<<"\n";
 	if(current_position[1]>=2.1)
 	{
		std::cout<<"Terminate Condition in right!!!\n";
 		return true;
 	}
	return false;
}
void terminate_in_right_condition::reset()
{
}
} // namespace generator
} // namespace common
} // namespace ecp
} // namespace mrrocpp
