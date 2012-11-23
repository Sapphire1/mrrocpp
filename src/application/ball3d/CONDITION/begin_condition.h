#ifndef BEGIN_CONDITION_H_
#define BEGIN_CONDITION_H_
#include "condition.h"
#include "base/lib/mrmath/mrmath.h"

class begin_condition : public condition
{
public:
	~begin_condition(){};
 	begin_condition(){};
 	bool check();
 	bool update(mrrocpp::lib::Xyz_Angle_Axis_vector &);
};

#endif

