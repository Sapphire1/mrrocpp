#include "terminate_beg_pos_condition.h"
#include "base/ecp/ecp_robot.h"
#include "base/ecp/ecp_generator.h"

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {
  
bool terminate_beg_pos_condition::check(mrrocpp::ecp::common::generator::behaviour* bh)
{
	bh->the_robot->ecp_command.instruction_type = lib::SET_GET;
	bh->the_robot->ecp_command.get_type = ARM_DEFINITION; // arm - ORYGINAL
	bh->the_robot->ecp_command.set_type = ARM_DEFINITION | ROBOT_MODEL_DEFINITION;
	bh->the_robot->ecp_command.robot_model.type = lib::TOOL_FRAME;
	bh->the_robot->ecp_command.get_robot_model_type = lib::TOOL_FRAME;
	bh->the_robot->ecp_command.set_arm_type = lib::PF_VELOCITY;
	bh->the_robot->ecp_command.motion_type = lib::ABSOLUTE;
	bh->the_robot->ecp_command.interpolation_type = lib::TCIM;
	bh->the_robot->ecp_command.motion_steps = 30;
	bh->the_robot->ecp_command.value_in_step_no = 30 - 2;


	bh->the_robot->ecp_command.instruction_type = lib::SET_GET;
		// read actual position
	  std::cout<<"Actual_position \n";

		for (int i = 0; i < 6; i++)
		{
			actual_position[i]=bh->the_robot->reply_package.arm.pf_def.joint_coordinates[i];
		}
    /*
 	if(actual_position[0]<0 && actual_position[1]<-1,5 && actual_position[2]<-0.0
 			&& actual_position[3]>0.0 && actual_position[4]>4.6 && actual_position[5]>=-0.023)
 	{
		std::cout<<"Terminate Condition of begin move!!!\n";
 		return true;
 	}*/

 	if(/*actual_position[0]<0 && actual_position[1]<-1,5 && actual_position[2]<-0.0
 	 			&& actual_position[3]>0.0 && actual_position[4]>4.6 && */actual_position[5]>=-0.023 && actual_position[5]<=0.0036)
 	 {
 			std::cout<<"Terminate Condition of begin move!!!\n";
 	 		return true;
 	 }
	return false;
}
void terminate_beg_pos_condition::reset()
{
}
} // namespace generator
} // namespace common
} // namespace ecp
} // namespace mrrocpp
