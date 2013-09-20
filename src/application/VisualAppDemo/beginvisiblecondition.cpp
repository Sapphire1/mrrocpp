/*
* beginvisiblecondition.cpp
*
* Created on: Dec 4, 2012
* Author: lzmuda
*/

#include "beginvisiblecondition.h"
#include "application/VisualApp/behaviour.h"
using namespace mrrocpp::ecp::common::generator;
namespace mrrocpp {
namespace ecp {
namespace condition {

begin_visible_condition::begin_visible_condition()
{
// TODO Auto-generated constructor stub

}

begin_visible_condition::~begin_visible_condition()
{
}

bool begin_visible_condition::check(const boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour> & bhvr)
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
	std::cout << "Begin_visible_condition : \n" << current_position[0]<<"\t"<<
	current_position[1]<<"\t\t"<< current_position[2]<<"\n"<< current_position[3]<<"\t\t"<<
	current_position[4]<<"\t"<< current_position[5]<<"\n";

	std::cout<<"begin_visible_condition::check()\n";
	boost::shared_ptr<visual_behaviour> bh = boost::dynamic_pointer_cast<visual_behaviour>(bhvr);
	if(!bh->sensor_configured)
	{
	  std::cout<<"Konfiguracja sensora\n";
	  bh->configure();
	  bh->sensor_configured=true;
	}
	lib::Homog_matrix tmp;
	bh->vs->get_sensor()->get_reading();
	bh->vs->get_position_change(tmp, 0.1);

	float diameter = bh->vs->get_objects_diameter();
	std::cout << "Diameter :" << diameter<< "\n";

	// diameter>0; manipulator is not too far; gripper is not twisted
	if(diameter>0 && current_position[1]>=1.8 && current_position[3]>=2.1 && current_position[4]>=2)
	{
		std::cout << "Object is visible and position is ok\n";
		std::cout<<"begin_visible_condition::check() end\n";
		return true;
	}
	else
	{
		std::cout << "Object is not visible or position is wrong\n";
		std::cout<<"begin_visible_condition::check() end\n";
		return false;
	}
	/* if()
	{
	std::cout<<"Begin Condition in left is not met!!!\n";
	return false;
	}
	std::cout<<"Begin Condition in left is met!!!\n";
	return true;
	*/
};

} /* namespace condition */
} /* namespace ecp */
} /* namespace mrrocpp */
