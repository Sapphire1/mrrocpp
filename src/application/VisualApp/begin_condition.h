/*!
 * @file begin_condition.h
 * @brief File containing the declaration of begin_condition class
 * @author lzmuda
 * @date 2012
 */

#ifndef BEGIN_CONDITION_H_
#define BEGIN_CONDITION_H_
#include "condition.h"
#include "base/lib/mrmath/mrmath.h"

using namespace mrrocpp::ecp::common::generator;

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {


/*!
 * @brief class for begin condition
 */

class begin_condition : public condition
{
public:
 	begin_condition(){};
	virtual ~begin_condition(){};

};

} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp

#endif

