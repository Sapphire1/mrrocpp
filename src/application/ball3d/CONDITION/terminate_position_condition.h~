#ifndef TERMINATE_POSITION_CONDITION_H_
#define TERMINATE_POSITION_CONDITION_H_
#include "terminate_condition.h"
#include "base/lib/mrmath/mrmath.h"

class terminate_position_condition : public terminate_condition
{
public:
	double limit;
	int opt; // opt==1 <=; opt==2 >=
	terminate_position_condition(){};
	terminate_position_condition(double lim, int option){limit=lim;opt=option;};
	~terminate_position_condition(){};
	bool update(mrrocpp::lib::Xyz_Angle_Axis_vector &);

};

#endif 
