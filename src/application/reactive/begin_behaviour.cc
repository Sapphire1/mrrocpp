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
	arm_stop=false;
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
	double current_position[6];

	for (int i = 0; i < 6; i++)
	{
		current_position[i]=the_robot->reply_package.arm.pf_def.joint_coordinates[i];
		std::cout<< current_position[i]<<"\t";
	}
	double sterowanie;
	double sterowanie2;
	double sterowanie3;
	double sterowanie4;
	double sterowanie5;
	double sterowanie6;

	if(!arm_stop)
	{
		sterowanie= (current_position[0]-0)/25;
		sterowanie2= -(-1.7 -current_position[1])/25;
		sterowanie3= -(current_position[2])/25;
		sterowanie5=-(4.6-current_position[4])/25;
		sterowanie6=-(current_position[5]+1.47)/25;
		sterowanie4=0;
		std::cout<<"sterowanie "<<sterowanie<< "\tsterowanie2 " << sterowanie2
					<< "\tsterowanie3 " << sterowanie3
					<< "\tsterowanie4 " << sterowanie4<< "\tsterowanie5 " << sterowanie5
					<< "\tsterowanie6 " << sterowanie6<<std::endl;
		if(current_position[0]<0.05 && current_position[0]>-0.05 && current_position[1]< -1.65 && current_position[1]>-1.7
		&& current_position[2]<0.05 && current_position[2]> -0.05)
		return false;
		//arm_stop=true;
	}
	else if(arm_stop)
	{
		sterowanie= (current_position[0]-0)/25;
				sterowanie2= -(-1.7 -current_position[1])/25;
				sterowanie3= -(current_position[2])/25;
				sterowanie5=-(4.6-current_position[4])/25;
				sterowanie6=-(current_position[5]+1.47)/25;
		sterowanie4=-(current_position[3])/25;
		std::cout<<"sterowanie "<<sterowanie<< "\tsterowanie2 " << sterowanie2
							<< "\tsterowanie3 " << sterowanie3
							<< "\tsterowanie4 " << sterowanie4<< "A POZYCJA4="<<current_position[3]<<"\tsterowanie5 " << sterowanie5
							<< "\tsterowanie6 " << sterowanie6<<std::endl;
		std::cout<<" arm_stop arm_stop arm_stop arm_stop arm_stop arm_stop arm_stop\n";
	}
	the_robot->ecp_command.arm.pf_def.arm_coordinates[0] = sterowanie;
	the_robot->ecp_command.arm.pf_def.arm_coordinates[1] = sterowanie2;
	the_robot->ecp_command.arm.pf_def.arm_coordinates[2] = sterowanie3;
	the_robot->ecp_command.arm.pf_def.arm_coordinates[3] = sterowanie4;
	the_robot->ecp_command.arm.pf_def.arm_coordinates[4] = sterowanie5;
	the_robot->ecp_command.arm.pf_def.arm_coordinates[5] = sterowanie6;

	if(current_position[3]<0.03 && current_position[3]>-0.03
			&& current_position[4]<0.03 && current_position[4]> -0.03)
		return false;

	counter++;
	std::cout<<"Counter: "<<counter <<std::endl;

	 
	return true;
}


} // namespace generator
} // namespace common
} // namespace ecp
} // namespace mrrocpp
