/*!
 * @file condition.h
 * @brief File containing the declaration of switch_task class
 * 
 * @author Lukasz Zmuda
 * @date 2012
 */


#include "begin_condition.h" 
#include <iostream>

bool begin_condition::check()
{
	if(get_any_begin_condition())
	{
		std::cout<<"Some begin condition is active!!!\n";
	}
	else 
	{
		if(get_any_terminate_condition())
		{
			std::cout<<"Some terminate condition is active!!! This have no sense...\n";
		}
		else
		{
			std::cout<<"Active begin condition!\n";
 			set_any_begin_condition(true);
			return true;
		}
	}
	return false;
}
bool begin_condition::update(mrrocpp::lib::Xyz_Angle_Axis_vector & actual_position){return check();}

