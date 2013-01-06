/*
 * beginvisiblecondition.h
 *
 *  Created on: Dec 4, 2012
 *      Author: sapphire
 */

#ifndef BEGINVISIBLECONDITION_H_
#define BEGINVISIBLECONDITION_H_

#include "../VisualApp/begin_condition.h"
#include "base/ecp/ecp_robot.h"
#include "base/ecp/ecp_generator.h"

namespace mrrocpp {
namespace ecp {
namespace condition {

class begin_visible_condition : public begin_condition
{
public:
	begin_visible_condition();
	virtual ~begin_visible_condition();
	bool check(const boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour> &);
	void reset(){;}
};

} /* namespace condition */
} /* namespace ecp */
} /* namespace mrrocpp */

#endif /* BEGINVISIBLECONDITION_H_ */
