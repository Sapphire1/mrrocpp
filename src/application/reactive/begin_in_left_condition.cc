#include "begin_in_left_condition.h"
#include "behaviour.h"
namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {


begin_in_left_condition::begin_in_left_condition(std::vector<double>  & a)
{
  limitation=a;
}

bool  begin_in_left_condition::check(mrrocpp::ecp::common::generator::behaviour* bhvr)
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
	std::cout << "In left\nCurrent position : \n" <<
	current_position[0]<<"\t"<< 	current_position[1]<<"\t\t"<< 	current_position[2]<<"\n"<<
	current_position[3]<<"\t\t"<< 	current_position[4]<<"\t"<< 	current_position[5]<<"\n";

	if(current_position[1]<=1.9)
	{
		std::cout<<"Begin Condition in left is not met!!!\n";
		return false;
	}
	std::cout<<"Begin Condition in left is met!!!\n";
	return true;
}
// ta bedzie wykorzystywana

} // namespace generator
} // namespace common
} // namespace ecp
} // namespace mrrocpp
