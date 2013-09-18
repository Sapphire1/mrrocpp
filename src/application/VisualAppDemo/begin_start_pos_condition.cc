/*
 * beginvisiblecondition.cpp
 *
 *  Created on: Dec 4, 2012
 *      Author: lzmuda
 */

#include "begin_start_pos_condition.h"
#include "application/VisualApp/behaviour.h"
namespace mrrocpp {
namespace ecp {
namespace condition {

begin_start_pos_condition::begin_start_pos_condition()
{
	// TODO Auto-generated constructor stub
}

begin_start_pos_condition::~begin_start_pos_condition()
{
}

bool begin_start_pos_condition::check(const boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour> & bhvr)
{
	lib::Homog_matrix actual_position_matrix;
	lib::Xyz_Angle_Axis_vector tool_vector;
	lib::Xyz_Angle_Axis_vector angle_axis_vector;
	std::vector<double> current_position(6);
	bhvr->the_robot->ecp_command.instruction_type = lib::GET;
	bhvr->the_robot->ecp_command.get_type = ARM_DEFINITION;

	// te dwie linie umozliwiaja odczytanie aktualnej pozycji
	bhvr->initiate_sensors_readings();
	bhvr->execute_motion();

	actual_position_matrix = bhvr->the_robot->reply_package.arm.pf_def.arm_frame;
	actual_position_matrix.get_xyz_angle_axis(angle_axis_vector);
	angle_axis_vector.to_vector(current_position);
	std::cout << "begin_start_pos_condition::check : \n" << current_position[0]<<"\t"<<
	current_position[1]<<"\t\t"<< current_position[2]<<"\n"<< 	current_position[3]<<"\t\t"<<
	current_position[4]<<"\t"<< current_position[5]<<"\n";
	//! if robot is synchronized
	/*if(		current_position[0]>=0.48 && current_position[0]<=0.55 &&
			current_position[1]>=1.8 && current_position[1]<=1.9 &&
			current_position[6] <=0.1 && current_position[6]>=-0.1)
	{
		std::cout<<"Start Condition is met!!!\n";
		return true;
	}*/
	if(current_position[0]>=0.48)
	{
			std::cout<<"Start Condition is met!!!\n";
			return true;
	}
	std::cout<<"Start Condition is not met!!!\n";
	return false;

};

} /* namespace condition */
} /* namespace ecp */
} /* namespace mrrocpp */
