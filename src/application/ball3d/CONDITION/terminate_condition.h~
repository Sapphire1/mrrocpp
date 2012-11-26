#ifndef TERMINATE_CONDITION_H_
#define TERMINATE_CONDITION_H_
#include "condition.h"
#include "base/lib/mrmath/mrmath.h"

class terminate_condition : public condition
{

public:
	terminate_condition(){};
	~terminate_condition(){};
	bool check(); // moze wywolywac ta metode w is_met od razu?
	bool update(mrrocpp::lib::Xyz_Angle_Axis_vector &);
};

#endif
