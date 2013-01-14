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




in_left_behaviour::in_left_behaviour(common::task::task& _ecp_task, boost::shared_ptr <mrrocpp::ecp::servovision::visual_servo_regulator> & reg) :	common::generator::behaviour(_ecp_task)
{
	this->reg=reg;
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
 	int capacity=500;
 	std::string server_addr="127.0.0.1";
 	int server_port=7000;
	//log_client = boost::shared_ptr <logger_client>(new logger_client(capacity, server_addr, server_port, "requestSentTime;sendTime;receiveTime;processingStart;processingEnd;object_visible;np_0_0;np_0_1;np_0_2;np_0_3;np_1_0;np_1_1;np_1_2;np_1_3;np_2_0;np_2_1;np_2_2;np_2_3;error_x;error_y;error_z;error_alpha;error_betha;error_gamma;"));

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
