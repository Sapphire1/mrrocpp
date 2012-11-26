#ifndef BEGIN_POSITION_CONDITION_H_
#define BEGIN_POSITION_CONDITION_H_
#include "begin_condition.h"
#include "base/lib/mrmath/mrmath.h"
#include <iostream>
#include <vector>

class begin_position_condition : public begin_condition
{	
public:
//   	wektor ograniczen
	std::vector<double> limitation;
	begin_position_condition(){};
	begin_position_condition(std::vector<double> &);
	~begin_position_condition(){};
	bool update(mrrocpp::lib::Xyz_Angle_Axis_vector &);
};

#endif


