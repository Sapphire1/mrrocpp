/*
 * begin_condition_right.h
 *
 *  Created on: Dec 4, 2012
 *      Author: sapphire
 */

#ifndef BEGIN_CONDITION_RIGHT_H_
#define BEGIN_CONDITION_RIGHT_H_

#include "../VisualApp/begin_condition.h"
#include "base/ecp/ecp_robot.h"
#include "base/ecp/ecp_generator.h"

//using namespace mrrocpp::ecp::condition;
using namespace mrrocpp::ecp::common::generator;
namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {

class begin_condition_right : public begin_condition
{
public:
	begin_condition_right();
	virtual ~begin_condition_right();
	bool check(const boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour> &);
	void reset(){;}
};

} /* namespace generator */
} /* namespace common */
} /* namespace ecp */
} /* namespace mrrocpp */

namespace mrrocpp {
namespace ecp {
namespace condition {

class begin_condition_right : public begin_condition
{
public:
	begin_condition_right();
	virtual ~begin_condition_right();
	bool check(const boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour> &);
	void reset(){;}
};

} /* namespace condition */
} /* namespace ecp */
} /* namespace mrrocpp */

#endif /* BEGIN_CONDITION_RIGHT_H_ */
