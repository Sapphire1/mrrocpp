#if !defined(_ECP_GEN_BALL3D_H)
#define _ECP_GEN_BALL3D_H

/*!
 * @file
 * @brief 
 * @author 
 *
 *
 * @ingroup generators
 */

#include "ecp_mp_g_ball3d.h"
#include "base/ecp/ecp_generator.h"
#include "base/lib/mrmath/mrmath.h"
#include "base/lib/logger_client/logger_client.h"
#include "../CONDITION/begin_position_condition.h"
#include "../CONDITION/terminate_position_condition.h"
#include "../CONDITION/switch_task2.h"
#include <vector>
using std::vector;

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {



using logger::logger_client;
using logger::log_message;
/*!
 * @brief 
 *
 * @author
 * @ingroup generators
 */
class ball3d : public common::generator::generator
{

public:

	int counter;
	/**
	 * @brief Constructor
	 * @param _ecp_task ecp task object referencex.
	 */
	ball3d(common::task::task& _ecp_task);

	/**
	 * @brief generates first step of transition function
	 * @return 
	 */
	bool first_step();
	bool next_step();
	void make_circle();
	void move_left();
	void move_right();
	boost::shared_ptr<logger_client> log;
};

typedef void (ball3d::*lala)();
} // namespace generator
} // namespace common
} // namespace ecp
} // namespace mrrocpp



#endif
