/**
 * @file begin_behaviour.cc
 * @brief 
 * @author lzmuda
 * @date 2012
 */

#include "begin_behaviour.h"
#include <iostream>

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {


begin_behaviour::begin_behaviour(common::task::task& _ecp_task) : common::generator::behaviour(_ecp_task)
{
	char config_section_name[] = { "[set_robot]" };
	reg = boost::shared_ptr <visual_servo_regulator> (new regulator_p(_ecp_task.config, config_section_name));

	arm_set=false;

	counter=0;
}

bool begin_behaviour::first_step()
{	

	the_robot->ecp_command.instruction_type = lib::SET_GET;
	the_robot->ecp_command.get_type = ARM_DEFINITION; // arm - ORYGINAL
	the_robot->ecp_command.set_type = ARM_DEFINITION | ROBOT_MODEL_DEFINITION;
	the_robot->ecp_command.robot_model.type = lib::TOOL_FRAME;
	the_robot->ecp_command.get_robot_model_type = lib::TOOL_FRAME;
	the_robot->ecp_command.set_arm_type = lib::PF_VELOCITY;
	the_robot->ecp_command.motion_type = lib::ABSOLUTE;
	the_robot->ecp_command.interpolation_type = lib::TCIM;
	the_robot->ecp_command.motion_steps = 30;
	the_robot->ecp_command.value_in_step_no = 30 - 2;

	return true;
}
bool begin_behaviour::next_step()
{	
	the_robot->ecp_command.instruction_type = lib::SET_GET;
	// read actual position
	for (int i = 0; i < 6; i++)
	{
		actual_position[i]=the_robot->reply_package.arm.pf_def.joint_coordinates[i];
		if(counter%50==0)
			std::cout<< actual_position[i]<<"\t";
	}

	if(!arm_set)
	{
		//	std::cout<<"\nSet arm\n";
			error[0]=(actual_position[0]);
			error[1]=actual_position[1]+1.571;
			error[2]=-actual_position[2];
	}
	else
	{
		//std::cout<<"\nArm is set, setting wrist and keeping position of arm\n";
		error[0]=(actual_position[0]);
		error[1]=actual_position[1]+1.571;
		error[2]=-actual_position[2];
		error[3]=actual_position[3];
		error[4]=-4.6+actual_position[4];
		error[5]=-actual_position[5]-1.47;
	}

	//! compute in regulator
	control = reg->compute_control(error,0.02);

	if( !arm_set && fabs(error[0])<0.0001 && fabs(error[1])<0.0001 && fabs(error[2]<0.0001))
			arm_set = true;

	for (int i = 0; i < 6; i++)
	{
		if(counter%50==0)
			std::cout<<std::endl<<"Control " << i <<"= "<<control[i]<<"\n";
		the_robot->ecp_command.arm.pf_def.arm_coordinates[i] = control[i];
	}
	counter++;

	if(error[5]<0.0001)
		return false;
	return true;
}


} // namespace generator
} // namespace common
} // namespace ecp
} // namespace mrrocpp
