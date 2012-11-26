#include "terminate_position_condition.h" 
#include <iostream>
bool terminate_position_condition::update(mrrocpp::lib::Xyz_Angle_Axis_vector & actual_position)
{
	double current_position[6];
//   jesli zachodzi warunek, sprawdz czy moze byc wykonana akcja
//   return true jesli moze byc wykonana akcja
	actual_position.to_table(current_position);
	std::cout << "get_position generator:" << std::endl;
 	for(size_t i = 0; i < 6; ++i) 
 	{
	    std::cout << current_position[i] << std::endl;
 	}
 if(opt==1)
 {
  std::cout<<"Sprawdzam pierwszy warunek konca\n";
  if(current_position[1]<=limit)
  {
    return check();
  }
 }
 if(opt==2)
 {
  std::cout<<"Sprawdzam drugi warunek konca\n";
  if(current_position[1]>=limit)
  {
    return check();
  }
 }
 return false;
}
