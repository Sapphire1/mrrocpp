#include "terminate_in_left_condition.h" 
#include "base/ecp/ecp_robot.h"
#include "base/ecp/ecp_generator.h"
using namespace mrrocpp::ecp::common::generator;
namespace mrrocpp {
namespace ecp {
namespace condition {
  
bool terminate_in_left_condition::check(mrrocpp::ecp::common::generator::behaviour* bh)
{
	std::cout<<"Terminate_position_condition::check()\n";
	lib::Homog_matrix tmp;
 	double current_position[6];
	lib::Xyz_Angle_Axis_vector tool_vector;
  	tmp=bh->the_robot->reply_package.arm.pf_def.arm_frame;
 	tmp.get_xyz_angle_axis(tool_vector);
 	tool_vector.to_table(current_position);
 	std::cout << "Pozycja 1: "<< current_position[1]<<"\n";
 	visual_behaviour* bhvr=dynamic_cast<visual_behaviour*>(bh);
 	std::cout<<"Wspolczynnik elipsy "<<bhvr->vs->get_ellipse_factor();

 	if(bhvr->vs->get_ellipse_factor()<=0.8 && bhvr->vs->get_ellipse_factor()>=0.5)
    {
    	std::cout<<"Wspolczynnik elipsy "<<bhvr->vs->get_ellipse_factor();
    	++counter;
    	if(counter>2)
    	{
    		std::cout<<"Terminate Condition in left!!!\n";
    		return true;
    	}
    }

 	if(current_position[1]<=1.7)
 	{
		std::cout<<"Terminate Condition in left!!!\n";
 		return true;
 	}
 	std::cout<<"Terminate_position_condition::check, end\n";
	return false;
}
void terminate_in_left_condition::reset()
{
}

} // namespace condition
} // namespace ecp
} // namespace mrrocpp
