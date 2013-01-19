/*!
 * @file
 * @brief 
 * @author lzmuda
 *
 * @ingroup generators
 */

#include "in_left_behaviour.h"
#include <iostream>


namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {




in_left_behaviour::in_left_behaviour(common::task::task& _ecp_task, boost::shared_ptr <mrrocpp::ecp::servovision::visual_servo_regulator> & reg,  boost::shared_ptr <logger_client> & log_client) :	common::generator::behaviour(_ecp_task)
{
//	log_client = boost::shared_ptr <logger_client>(new logger_client(500, "127.0.0.1", 7000,"X;Y;Z;AX;AY;AZ"));
//	log_client->set_connect();
	this->reg=reg;
	this->log_client=log_client;
}

bool in_left_behaviour::first_step()
{	

	the_robot->ecp_command.instruction_type = lib::GET;
	the_robot->ecp_command.get_type = ARM_DEFINITION;
	the_robot->ecp_command.set_type = ARM_DEFINITION;
	the_robot->ecp_command.set_arm_type = lib::FRAME;
	the_robot->ecp_command.motion_type = lib::RELATIVE;
	the_robot->ecp_command.interpolation_type = lib::MIM;
 	the_robot->ecp_command.motion_steps = 100;
 	the_robot->ecp_command.value_in_step_no = 97;

	return true;
}

bool in_left_behaviour::next_step()
{	
	lib::Homog_matrix tmp;
	double current_position[6];
	lib::Xyz_Angle_Axis_vector tool_vector;
	tmp=the_robot->reply_package.arm.pf_def.arm_frame;
	tmp.get_xyz_angle_axis(tool_vector);
	tool_vector.to_table(current_position);
	for(int i=0; i<6; i++)
		std::cout<<current_position[i]<<"\t";
	std::cout<<std::endl;
	sprintf(msg.text, "%f;%f;%f;%f;%f;%f;",current_position[0],current_position[1],current_position[2],current_position[3],current_position[4],current_position[5]);

	if (log_client.get() != NULL) {
		std::cout<<"logowanie\n";
		log_client->log(msg);
	}

	error[1]=current_position[1]-1.8;
	control = reg->compute_control(error, 0.02);

	lib::Homog_matrix homog_matrix;
	double nextChange[6];
	the_robot->ecp_command.instruction_type = lib::SET_GET;
	nextChange[0]=0;
	nextChange[1]=control[1];
	nextChange[2]=0;
	nextChange[3]=0;
	nextChange[4]=0;
	nextChange[5]=0;
	homog_matrix.set_from_xyz_angle_axis(lib::Xyz_Angle_Axis_vector(nextChange[0], nextChange[1], nextChange[2], nextChange[3], nextChange[4], nextChange[5]));

	the_robot->ecp_command.arm.pf_def.arm_frame = homog_matrix;
	the_robot->ecp_command.instruction_type = lib::SET_GET;

	// Obliczenie zadanej pozycji posredniej w tym kroku ruchu

	lib::Homog_matrix current_frame_wo_offset(the_robot->reply_package.arm.pf_def.arm_frame);
	current_frame_wo_offset.remove_translation();

	lib::Ft_v_vector force_torque(the_robot->reply_package.arm.pf_def.force_xyz_torque_xyz);
	std::cout<< "Next_STEP \n"<<std::endl;

	 return true;
}


} // namespace generator
} // namespace common
} // namespace ecp
} // namespace mrrocpp
