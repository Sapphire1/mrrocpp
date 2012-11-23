#include "terminate_condition.h" 
#include <iostream>


bool terminate_condition::check()
{
	if(get_any_begin_condition())						// begin 1->0 terminate 0->1; zatrzymanie generatora
	{
		std::cout<<"Terminate!\n";
		set_any_terminate_condition(false);
		set_any_begin_condition(false);
		return true;
	}
	else									// begin 0 terminate 1; blad nie ma czego zatrzymac
	{
		std::cout<<"Some begin condition have to be active befor termination condition\n";
		return false;
	}
}


bool terminate_condition::update(mrrocpp::lib::Xyz_Angle_Axis_vector & actual_position){return check();}