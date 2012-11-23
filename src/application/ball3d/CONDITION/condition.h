#ifndef CONDITION_H_
#define CONDITION_H_
#include <vector>
#include "base/lib/mrmath/mrmath.h"
using std::vector;
// using namespace mrrocpp::lib;
/*
przejscia
begin	terminate	status
0->1	0		OK				
0->1	1		ERROR
1->0	0		ERROR		// sam sie wylaczyc nie moze
1->0	1		OK
1->1    ?		ERROR		// juz jeden jest aktywny

begin	terminate	status
0	0->1		ERROR		// nie ma czego wylaczyc				
0	1->0		OK	 
1	0->1		OK
1	1->0		ERROR
*/

class condition
{
private:
	static bool any_begin_condition_met;
	static bool any_terminate_condition_met;
	
public:
	condition(){any_begin_condition_met=false; any_terminate_condition_met=false;};
	~condition(){};
	virtual bool update(mrrocpp::lib::Xyz_Angle_Axis_vector &)=0;	// update readed values (ie. manipulator position); implentation in real class
	virtual bool check()=0;
	static bool get_any_begin_condition();
	static void set_any_terminate_condition(bool);
	static bool get_any_terminate_condition();
	static void set_any_begin_condition(bool);
};


#endif