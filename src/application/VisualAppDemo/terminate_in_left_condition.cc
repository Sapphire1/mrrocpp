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
	float diameter;
 	double current_position[6];
	lib::Xyz_Angle_Axis_vector tool_vector;
  	tmp=bh->the_robot->reply_package.arm.pf_def.arm_frame;
 	tmp.get_xyz_angle_axis(tool_vector);
 	tool_vector.to_table(current_position);
 	visual_behaviour* bhvr=dynamic_cast<visual_behaviour*>(bh);
 	std::cout<<"Wspolczynnik elipsy "<<bhvr->vs->get_ellipse_factor();

 	while((diameter = bhvr->vs->get_objects_diameter())==0 || bhvr->vs->get_ellipse_factor()<0.7)
 	{
 		bhvr->vs->get_sensor()->get_reading();
 		bhvr->vs->get_position_change(tmp, 0.1);
 		std::cout << "Terminate hybrid behaviour: Srednica obiektu to :" << diameter<< "\n";
 	}

 	if(bhvr->vs->get_ellipse_factor()<=0.70 && bhvr->vs->get_ellipse_factor()>=0.5)
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
