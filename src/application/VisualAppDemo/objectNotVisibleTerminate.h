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


	lib::Homog_matrix position;
};

} /* namespace condition */
} /* namespace ecp */
} /* namespace mrrocpp */
#endif /* OBJECTNOTVISIBLETERMINATE_H_ */
