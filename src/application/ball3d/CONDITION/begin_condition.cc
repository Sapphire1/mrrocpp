#include "begin_condition.h" 
#include <iostream>

bool begin_condition::check()
{
	if(get_any_begin_condition())						// begin 1->1
	{
		std::cout<<"Some begin condition is active!!!\n";
	}
	else // trzeba sprawdzic czy terminate jest aktywna
	{
		if(get_any_terminate_condition())				// begin 0->1 terminate 1
		{
			std::cout<<"Some terminate condition is active!!! This have no sense...\n";
		}
		else								// begin 0->1 terminate 0
		{
			std::cout<<"Active begin condition!\n";
 			set_any_begin_condition(true);
			return true;
		}
	}
	return false;
}
bool begin_condition::update(mrrocpp::lib::Xyz_Angle_Axis_vector & actual_position){return check();}

