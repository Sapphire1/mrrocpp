/*
 * beginvisiblecondition.cpp
 *
 *  Created on: Dec 4, 2012
 *      Author: lzmuda
 */

#include "beginvisiblecondition.h"
#include "application/VisualApp/behaviour.h"
namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {

begin_visible_condition::begin_visible_condition()
{
	// TODO Auto-generated constructor stub

}

begin_visible_condition::~begin_visible_condition()
{
}

bool begin_visible_condition::check(mrrocpp::ecp::common::generator::behaviour * bhvr)
{

	bhvr->the_robot->ecp_command.instruction_type = lib::GET;
	bhvr->the_robot->ecp_command.get_type = ARM_DEFINITION;

	bhvr->the_robot->ecp_command.motion_type = lib::ABSOLUTE;
	bhvr->the_robot->ecp_command.set_type = ARM_DEFINITION;
	bhvr->the_robot->ecp_command.set_arm_type = lib::FRAME;
	bhvr->the_robot->ecp_command.interpolation_type = lib::TCIM;
	bhvr->the_robot->ecp_command.motion_steps = 30;
	  //the_robot->ecp_command.value_in_step_no = motion_steps - motion_steps_value_in_step_no;
	bhvr->the_robot->ecp_command.value_in_step_no = 40;
	for (int i = 0; i < 6; i++) {
		bhvr->the_robot->ecp_command.arm.pf_def.behaviour[i] = lib::UNGUARDED_MOTION;
	  }

			// order to prepare data for sensors
	//      jak to nizej mam wlaczone to czyta tylko za pierwszym razem!
	//		jak mam wylaczone to za pierwszym razem nie czyta!
	//		bhvr->initiate_sensors_readings();
			bhvr->the_robot->is_new_data = false;
			bhvr->the_robot->is_new_request = false;
			bhvr->the_robot->create_command();
			if (bhvr->the_robot->data_ports_used)
			{
				bhvr->the_robot->finalize_data_port_command();
			}

			if (bhvr->the_robot->communicate_with_edp)
			{
//				bhvr->execute_motion();
				bhvr->the_robot->get_reply();
			}

	std::vector<double> current_position(6);
	lib::Xyz_Angle_Axis_vector tool_vector;

	lib::Homog_matrix actual_position_matrix;
	actual_position_matrix = bhvr->the_robot->reply_package.arm.pf_def.arm_frame;
	lib::Xyz_Angle_Axis_vector angle_axis_vector;
	actual_position_matrix.get_xyz_angle_axis(angle_axis_vector);
	angle_axis_vector.to_vector(current_position);
		  std::cout << current_position[0]<<"\t"<<
		  current_position[1]<<"\t"<<
		  current_position[2]<<"\n"<<
		  current_position[3]<<"\t"<<
		  current_position[4]<<"\t"<<
		  current_position[5]<<"\n";
	 	if(current_position[1]<=1.98 || current_position[1]>=2.1)
	 	{
			std::cout<<"Begin Condition in left is not met!!!\n";
	 		return true;
	 	}
		return true;
};

} /* namespace generator */
} /* namespace common */
} /* namespace ecp */
} /* namespace mrrocpp */
