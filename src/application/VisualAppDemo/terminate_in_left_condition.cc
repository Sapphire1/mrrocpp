#include "terminate_in_left_condition.h" 
#include "base/ecp/ecp_robot.h"
#include "base/ecp/ecp_generator.h"
using namespace mrrocpp::ecp::common::generator;
namespace mrrocpp {
namespace ecp {
namespace condition {
  
bool terminate_in_left_condition::check(mrrocpp::ecp::common::generator::behaviour* bh)
{
	std::cout<<"terminate_position_condition::check()\n";
	lib::Homog_matrix tmp;
 	double current_position[6];
	lib::Xyz_Angle_Axis_vector tool_vector;
  	tmp=bh->the_robot->reply_package.arm.pf_def.arm_frame;
 	tmp.get_xyz_angle_axis(tool_vector);
 	tool_vector.to_table(current_position);
 			  std::cout << current_position[0]<<"\t"<<
 			  current_position[1]<<"\t"<<
 			  current_position[2]<<"\n"<<
 			  current_position[3]<<"\t"<<
 			  current_position[4]<<"\t"<<
 			  current_position[5]<<"\n";
 	visual_behaviour* bhvr=dynamic_cast<visual_behaviour*>(bh);
 	std::cout<<"Wspolczynnik elipsy "<<bhvr->vs->get_ellipse_factor();
 	std::cout<<"Counter "<< counter;

 	if(bhvr->vs->get_ellipse_factor()<=0.8 &&bhvr->vs->get_ellipse_factor()>=0.5)
    {
    	std::cout<<"Wspolczynnik elipsy "<<bhvr->vs->get_ellipse_factor();
    	++counter;
    	if(counter>2)
    	{
    		std::cout<<"Terminate Condition in left!!!\n";
    		return true;
    	}
    }

 	if(current_position[5]<=-0.7)
 	{
		std::cout<<"Terminate Condition in left!!!\n"<<
		current_position[5]<<"\n";
 		return true;
 	}
	return false;
}
void terminate_in_left_condition::reset()
{
}

} // namespace condition
} // namespace ecp
} // namespace mrrocpp
