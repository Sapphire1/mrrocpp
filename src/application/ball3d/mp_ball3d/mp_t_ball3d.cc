#include "mp_t_ball3d.h"

// ecp generators to be commanded
#include "../generator_ball3d/ecp_mp_g_ball3d.h"
// mp_robots headers
// #include "robot/irp6ot_m/mp_r_irp6ot_m.h"
#include "robot/irp6p_m/mp_r_irp6p_m.h"

namespace mrrocpp {
namespace mp {
namespace task {

// powolanie robotow w zaleznosci od zawartosci pliku konfiguracyjnego
void ball3d::create_robots()
{
// 	ACTIVATE_MP_ROBOT(irp6ot_m);
	ACTIVATE_MP_ROBOT(irp6p_m);
}

ball3d::ball3d(lib::configurator &_config) : task(_config)
{
}

void ball3d::main_task_algorithm(void)
{


  
	sr_ecp_msg->message("Ball3D irp6 (MP) START");


	
	sr_ecp_msg->message("Both Bias - Ball3D");
 
// 	set_next_ecp_state(ecp_mp::generator::ECP_GEN_BALL3D, 0, "", lib::irp6ot_m::ROBOT_NAME);
	set_next_ecp_state(ecp_mp::generator::ECP_GEN_BALL3D, 0, "", lib::irp6p_m::ROBOT_NAME);
	wait_for_task_termination(false /*,lib::irp6ot_m::ROBOT_NAME*/, lib::irp6p_m::ROBOT_NAME);

	sr_ecp_msg->message("Ball3D END");

}

task* return_created_mp_task(lib::configurator &_config)
{
	return new ball3d(_config);
}

} // namespace task
} // namespace mp
} // namespace mrrocpp
