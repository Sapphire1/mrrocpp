/**
 * timeout_terminate_condition.h
 *
 *  Created on: Dec 3, 2012
 *      Author: lzmuda
 */

#ifndef TIMEOUT_TERMINATE_CONDITION_H_
#define TIMEOUT_TERMINATE_CONDITION_H_

#include <time.h>
#include "application/VisualApp/terminate_condition.h"

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {

/** @addtogroup servovision
 *  @{
 */

/**
 *
 */
class timeout_terminate_condition : public terminate_condition
{
public:
	timeout_terminate_condition();
	timeout_terminate_condition(double timeout);
	virtual ~timeout_terminate_condition();
	void reset();
 	bool check(const boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour>&){return false;};
 	bool check(mrrocpp::ecp::common::generator::behaviour *);
protected:
	double timeout;
	double start_time;
	double get_time_s()const;
};

/** @} */

}//namespace generator
}
}
}

#endif /* TIMEOUT_TERMINATE_CONDITION_H_ */
