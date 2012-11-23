#if !defined(__MP_T_BALL3D_H)
#define __MP_T_BALL3D_H

#include "base/mp/mp_task.h"

namespace mrrocpp {
namespace mp {
namespace task {

/**
 * @defgroup swarm_demo swarm_demo
 * @ingroup application
 * A swarm demo application
 */

class ball3d : public task
{
protected:

public:

	/**
	 * Constructor.
	 */
	ball3d(lib::configurator &_config);
	/// utworzenie robotow
	void create_robots(void);
	void main_task_algorithm(void);
	void switch_task(void);

};

} // namespace task
} // namespace mp
} // namespace mrrocpp

#endif
