/*
 * object_reached_termination_condition.h
 *
 *  Created on: Apr 29, 2010
 *      Author: mboryn
 */

#ifndef OBJECT_REACHED_TERMINATION_CONDITION_H_
#define OBJECT_REACHED_TERMINATION_CONDITION_H_

#include <string>
#include "base/lib/configurator.h"
#include "application/VisualApp/terminate_condition.h"
#include "visual_behaviour.h"
namespace mrrocpp {

namespace ecp {

namespace condition {
// class behaviour;
/** @addtogroup servovision
 *  @{
 */

/**
 *
 */
class object_reached_termination_condition: public terminate_condition
{
public:
	object_reached_termination_condition(const lib::configurator& config, const std::string &section_name);
	virtual ~object_reached_termination_condition();
	virtual void reset();
	bool check(mrrocpp::ecp::common::generator::behaviour * v_bhr);
	bool check(const boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour> &){return true;};
	
	lib::Homog_matrix get_position() const;
protected:
	double max_linear_speed;
	double max_angular_speed;
	double max_linear_accel;
	double max_angular_accel;
	double max_linear_error;
	double max_angular_error;
	int min_steps;
	int steps_delay;

	lib::Homog_matrix position;
};

/** @} */



}	//namaspace condition

}

}

#endif /* OBJECT_REACHED_TERMINATION_CONDITION_H_ */
