/*!
 * @file
 * @brief 
 * @author lzmuda
 *
 * @ingroup generators
 */

#include "in_right_behaviour.h"
#include <iostream>


namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {




in_right_behaviour::in_right_behaviour(common::task::task& _ecp_task) : common::generator::behaviour(_ecp_task)
{

}

bool in_right_behaviour::first_step()
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
bool in_right_behaviour::next_step()
{	
	lib::Homog_matrix homog_matrix;
	double nextChange[6];
	the_robot->ecp_command.instruction_type = lib::SET_GET;
	nextChange[0]=0;
	nextChange[1]=0.02;
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
