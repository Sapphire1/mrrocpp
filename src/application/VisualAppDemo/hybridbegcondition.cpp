/*
 * hybridbegcondition.cpp
 *
 *  Created on: 22-01-2013
 *      Author: lzmuda
 */

#include "hybridbegcondition.h"
#include "application/VisualApp/behaviour.h"
#include <ctime>
using namespace mrrocpp::ecp::common::generator;
namespace mrrocpp {
namespace ecp {
namespace condition {


hybrid_beg_condition::hybrid_beg_condition() {


}

hybrid_beg_condition::~hybrid_beg_condition() {
	// TODO Auto-generated destructor stub
}


bool hybrid_beg_condition::check(const boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour> & bhvr)
{
	std::time_t t;
	std::cout<<"hybrid_beg_condition::check\n";
	lib::Homog_matrix actual_position_matrix;
	lib::Xyz_Angle_Axis_vector tool_vector;
	lib::Xyz_Angle_Axis_vector angle_axis_vector;
	std::vector<double> current_position(6);
	bhvr->the_robot->ecp_command.instruction_type = lib::GET;
	bhvr->the_robot->ecp_command.get_type = ARM_DEFINITION;

	actual_position_matrix = bhvr->the_robot->reply_package.arm.pf_def.arm_frame;
	actual_position_matrix.get_xyz_angle_axis(angle_axis_vector);
	angle_axis_vector.to_vector(current_position);
	std::cout << "Begin_visible_condition : \n" << current_position[0]<<"\t"<<
	current_position[1]<<"\t"<< current_position[2]<<"\n"<< 	current_position[3]<<"\t"<<
	current_position[4]<<"\t"<< current_position[5]<<"\n";
	boost::shared_ptr<visual_behaviour> bh = boost::dynamic_pointer_cast<visual_behaviour>(bhvr);
	if(!bh->sensor_configured)
	{
	  std::cout<<"Konfiguracja sensora\n";
	  bh->configure();
	  bh->sensor_configured=true;
	}
	lib::Homog_matrix tmp;

	float diameter;

	bh->vs->get_sensor()->get_reading();
	t = std::time(0);  // t is an integer type
	std::cout << t << " seconds since 01-Jan-1970\n";
	bh->vs->get_position_change(tmp, 0.1);

	while((diameter = bh->vs->get_objects_diameter())==0 || bh->vs->get_ellipse_factor()<0.6)
	{
		bh->vs->get_sensor()->get_reading();
		bh->vs->get_position_change(tmp, 0.1);
		std::cout << "Srednica obiektu to :" << diameter<< "\n";
		t = std::time(0);  // t is an integer type
		std::cout << t << " seconds since 01-Jan-1970\n";
	}
	std::cout << "Srednica obiektu to :" << diameter<< "\n";
	t = std::time(0);  // t is an integer type
	std::cout << t << " seconds since 01-Jan-1970\n";
	if(diameter>0 && current_position[1]>=1.8)
	{
		std::cout<<"Hybride Begin Condition in left is met!!!\n";
		std::cout<<"hybrid_beg_condition::check end\n";
		return true;
	}
	std::cout<<"Hybride Begin Condition in left is not met!!!\n";
	std::cout<<"hybrid_beg_condition::check end\n";
	return false;


};

} /* namespace condition */
} /* namespace ecp */
} /* namespace mrrocpp */
