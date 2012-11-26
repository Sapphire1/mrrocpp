#include "begin_position_condition.h"
#include <iostream>

begin_position_condition::begin_position_condition(std::vector<double>  & a)
{
  limitation=a;
  
}
bool begin_position_condition::update(mrrocpp::lib::Xyz_Angle_Axis_vector & actual_position)
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
// uruchom zadanie jesli manipulator jest w odpowiedniej pozycji
      std::cout<<"Wykonanie z ograniczeniem dolnym: "<< limitation[0]<<std::endl;
      if(current_position[1]>=limitation[0] && current_position[1]<=limitation[1])
      {
	return check();
      }
      return false;
}