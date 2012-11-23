/*
 * ecp_t_vs_tutorial.cc
 *
 *  Created on: Apr 21, 2010
 *      Author: mboryn
 */

// Moje zadanie przelaczania zadan powinno przyjac liste generatorow i wykonywac na nich caly operacje move() tak długo, aż nie będzie termination
// No tak, tylko to bez sensu bo move pozapierdala, chyba, że od razu będzie zwracał false...
// to wtedy mozna zrobic tak ze wywolac first step i tak dlugo next step, az nie bedzie spelniony warunek
// tylko wtedy jest to sprzeczne z tym co jest teraz zrobine, sprzeczne z Move()

#include "ecp_g_ball3dv2.h"

#include "robot/irp6p_m/ecp_r_irp6p_m.h"
#include "robot/irp6ot_m/ecp_r_irp6ot_m.h"

using namespace mrrocpp::ecp::common::generator;

namespace mrrocpp {

namespace ecp {

namespace common {

namespace task {
ball3d::ball3d(lib::configurator &_config) : common::task::task(_config)
{
	// the robot is choose dependently on the section of configuration file sent as argv[4]
// 	if (config.robot_name == lib::irp6ot_m::ROBOT_NAME) {
// 		ecp_m_robot = (boost::shared_ptr <robot_t>) new irp6ot_m::robot(*this);
// 	} /*else */
	if(config.robot_name == lib::irp6p_m::ROBOT_NAME) 
	{
		ecp_m_robot = (boost::shared_ptr <robot_t>) new irp6p_m::robot(*this);
	} 
	else 
	{
		throw std::runtime_error("Robot not supported");
	}
	sr_ecp_msg->message("Creating visual servo...");		
}//ball3d()


void ball3d::main_task_algorithm(void)
{
	sr_ecp_msg->message("Creating visual servo...");
	move_visual_servo();

	termination_notice();
}

void ball3d::move_visual_servo()
{

      b3d= new generator::ball3d(*this);
      b3d->first_step();
      b3d->next_step();
      delete b3d;

      sr_ecp_msg->message("Creating visual servo...");
	
}

task_base* return_created_ecp_task(lib::configurator &config)
{
	return new ball3d(config);
}

} // namespace task

}//namespace common

}//namespace ecp

}//namespace mrrocpp
