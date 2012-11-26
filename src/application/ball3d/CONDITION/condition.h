/*!
 * @file condition.h
 * @brief File containing the declaration of switch_task class
 * 
 * @author Lukasz Zmuda
 * @date 2012
 */

#ifndef CONDITION_H_
#define CONDITION_H_
#include <vector>
#include "base/lib/mrmath/mrmath.h"
using std::vector;

/*!
 * @brief virtual class from which inheriting classes: begin_condition and terminate_condition
 */

class condition
{
private:
	/*!
	* @brief Fields designed for storing information about this if any begin condition and terminate condition is active
	*/
	
	static bool any_begin_condition_met;
	static bool any_terminate_condition_met;
	
public:
	/*!
	* @brief Constructor responsible for initializing state of two fields
	*/
	condition()
	{
	  any_begin_condition_met=false; 
	  any_terminate_condition_met=false;
	};
	/*!
	* @brief Destructor
	*/
	~condition(){};
	
	/*!
	* @brief Check if condition can to be activated
	*/
	virtual bool check()=0;
	
	/*!
	* @brief Checking if the status of the condition needs to be changed
	* @param reference to homogeneous matrix
	*/
	virtual bool update(mrrocpp::lib::Xyz_Angle_Axis_vector &)=0;	// update readed values (ie. manipulator position); implentation in real class
	
	/*!
	* @brief Getters and setters
	*/
	
	static bool get_any_begin_condition();
	static void set_any_terminate_condition(bool);
	static bool get_any_terminate_condition();
	static void set_any_begin_condition(bool);
};

#endif