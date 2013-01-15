/*
 * begin_start_pos_condition.h
 *
 *  Created on: Jan 15, 2013
 *      Author: sapphire
 */

#ifndef BEGIN_START_POS_CONDITION_H_
#define BEGIN_START_POS_CONDITION_H_

#include "../VisualApp/begin_condition.h"
#include "base/ecp/ecp_robot.h"
#include "base/ecp/ecp_generator.h"

namespace mrrocpp {
namespace ecp {
namespace condition {

class begin_start_pos_condition : public begin_condition
{
public:
	begin_start_pos_condition();
	virtual ~begin_start_pos_condition();
	bool check(const boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour> &);
	void reset(){;}
};

} /* namespace condition */
} /* namespace ecp */
} /* namespace mrrocpp */

#endif /* BEGIN_START_POS_CONDITION_H_ */
