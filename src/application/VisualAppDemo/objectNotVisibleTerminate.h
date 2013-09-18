/*
 * objectNotVisibleTerminate.h
 *
 *  Created on: 18-09-2013
 *      Author: lzmuda
 */

#ifndef OBJECTNOTVISIBLETERMINATE_H_
#define OBJECTNOTVISIBLETERMINATE_H_

#include "base/lib/configurator.h"
#include "application/VisualApp/terminate_condition.h"
#include "visual_behaviour.h"

namespace mrrocpp {
namespace ecp {
namespace condition {

class objectNotVisibleTerminate : public terminate_condition{
public:
	objectNotVisibleTerminate();
	objectNotVisibleTerminate(const lib::configurator& config, const std::string &section_name);
	virtual ~objectNotVisibleTerminate();
	virtual void reset();
	bool check(mrrocpp::ecp::common::generator::behaviour * v_bhr);
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

} /* namespace condition */
} /* namespace ecp */
} /* namespace mrrocpp */
#endif /* OBJECTNOTVISIBLETERMINATE_H_ */
