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


begin_behaviour::begin_behaviour(common::task::task& _ecp_task, boost::shared_ptr<logger::logger_client>& log_client) : common::generator::behaviour(_ecp_task)
{
	char config_section_name[] = { "[set_robot]" };
	reg = boost::shared_ptr <visual_servo_regulator> (new regulator_p(_ecp_task.config, config_section_name));
	arm_set=false;
	wrist_set=false;
	counter=0;
	this->log_client=log_client;
}

bool begin_behaviour::first_step()
{	
	std::cout<<"Begin behaviour :: firstStep\n";
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
		std::cout<< actual_position[i]<<"\t";
	}

	if(!arm_set)
	{
		//	std::cout<<"\nSet arm\n";
			error[0]=(actual_position[0]);
			error[1]=actual_position[1]+1.571;
			error[2]=-actual_position[2];
	}
	else if(arm_set && !wrist_set)
	{
		//std::cout<<"\nArm is set, setting wrist and keeping position of arm\n";
		error[0]=(actual_position[0]);
		error[1]=actual_position[1]+1.571;
		error[2]=-actual_position[2];
		error[3]=actual_position[3];
		error[4]=-4.7+actual_position[4];
		error[5]=-actual_position[5]-1.4;
	}
	else if(arm_set && wrist_set)
	{
		std::cout<<"Wrist!!\n";
		error[0]=error[1]=error[2]=error[3]=error[4]=0;
		error[5]=-actual_position[5];
	}
	double current_position[6];
	lib::Homog_matrix tmp;
	lib::Xyz_Angle_Axis_vector tool_vector;
	tmp=the_robot->reply_package.arm.pf_def.arm_frame;
	tmp.get_xyz_angle_axis(tool_vector);
	tool_vector.to_table(current_position);
	double ellipse_factor=0.0;
	sprintf(msg.text, "%f;%f;%f;%f;%f;%f;%f",ellipse_factor,current_position[0],current_position[1],current_position[2],current_position[3],current_position[4],current_position[5]);
	if (log_client.get() != NULL)
	{
		 log_client->log(msg);
	}

	//! compute in regulator
	control = reg->compute_control(error,0.02);

	if(control[4]<(-0.15))
		control[4]=-0.15;

	if(control[5]<0.2 && wrist_set &&control[5]>0.005)
		control[5]=0.2;
	else if(control[5]<0.03 && !wrist_set)
			control[5]=0.03;

	if( !arm_set && fabs(error[0])<0.01 && fabs(error[1])<0.01 && fabs(error[2]<0.01))
		arm_set = true;
	if(arm_set && (actual_position[5]>=-1.5))
	{
		wrist_set=true;
	}
	for (int i = 0; i < 6; i++)
	{
		std::cout<<std::endl<<"Control " << i <<"= "<<control[i]<<"\n";
		the_robot->ecp_command.arm.pf_def.arm_coordinates[i] = control[i];
	}

	return true;
}


} // namespace generator
} // namespace common
} // namespace ecp
} // namespace mrrocpp
