/**
 * timeout_terminate_condition.cc
 *
 *  Created on: Dec 3, 2012
 *      Author: lzmuda
 */

#include <stdexcept>
#include "timeout_terminate_condition.h"
#include "base/lib/logger.h"

using namespace std;
using namespace logger;

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {

timeout_terminate_condition::timeout_terminate_condition(double timeout) :
	timeout(timeout)
{
	reset();
}

timeout_terminate_condition::~timeout_terminate_condition()
{
}

void timeout_terminate_condition::reset()
{
	start_time = get_time_s();
}

bool timeout_terminate_condition::check(mrrocpp::ecp::common::generator::behaviour * bh)
{
	if (get_time_s() - start_time >= timeout) {
		return true;
	}
	return false;
}

double timeout_terminate_condition::get_time_s()const
{
	struct timespec current_time;
	if (clock_gettime(CLOCK_REALTIME, &current_time) == -1) {
		throw std::logic_error("timeout_terminate_condition::get_time_s(): clock_gettime");
	}

	return current_time.tv_sec + ((double) current_time.tv_nsec) * 1e-9;

}

}//namespace generator
}
}
}
