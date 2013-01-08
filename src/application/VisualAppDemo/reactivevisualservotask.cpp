/*
 * reactivevisualservotask.cpp
 *
 *  Created on: Dec 3, 2012
 *      Author: lzmuda
 */

#include "reactivevisualservotask.h"
using namespace logger;
using namespace mrrocpp::ecp::servovision;
using namespace mrrocpp::ecp::condition;

namespace mrrocpp {

namespace ecp {

namespace common {

namespace task {

reactive_visual_servo_task::reactive_visual_servo_task(mrrocpp::lib::configurator & configurator) : common::task::reactive_task(configurator)
{
	log_dbg_enabled = true;
	log_enabled = true;
	try{
	 	if(config.robot_name == lib::irp6p_m::ROBOT_NAME)
		{
			ecp_m_robot = (boost::shared_ptr <robot_t>) new irp6p_m::robot(*this);
		}
		else
		{
			throw std::runtime_error("Robot not supported");
		}

	 	char config_section_name[] = { "[object_follower_ib]" };
	 	char config_section_name_wrist[] = { "[servovision_wrist]" };
	 	char config_section_name_arm[] = { "[servovision_arm]" };

	 	log_dbg("reactive_servo_task: 1\n");

	 	reg_wrist = boost::shared_ptr <visual_servo_regulator> (new regulator_p(configurator, config_section_name_wrist));
	 	reg_arm = boost::shared_ptr <visual_servo_regulator> (new regulator_p(configurator, config_section_name_arm));

	 	log_dbg("reactive_servo_task: 2\n");
	 	ds = boost::shared_ptr <mrrocpp::ecp_mp::sensor::discode::discode_sensor>(new mrrocpp::ecp_mp::sensor::discode::discode_sensor(configurator, config_section_name));
	 	//ds_2 = boost::shared_ptr <mrrocpp::ecp_mp::sensor::discode::discode_sensor>(new mrrocpp::ecp_mp::sensor::discode::discode_sensor(configurator, config_section_name));
	 	log_dbg("reactive_servo_task: 3\n");

	 	arm_vs = shared_ptr <visual_servo> (new ib_eih_visual_servo(reg_arm, ds, config_section_name, configurator));
	 	wrist_vs = shared_ptr <visual_servo> (new ib_eih_wrist_move(reg_wrist, ds, config_section_name, configurator));
	 	log_dbg("reactive_servo_task: 4.5\n");

	 	v_bhr_1= boost::shared_ptr<behaviour>(new visual_behaviour(*this, config_section_name, arm_vs));
	 	v_bhr2= boost::shared_ptr<behaviour>(new visual_behaviour(*this, config_section_name, wrist_vs));
	 	obj_reach_ter_cond = boost::shared_ptr <terminate_condition>(new object_reached_termination_condition(configurator, config_section_name_arm));
	 	log_dbg("reactive_servo_task: 5\n");

	 	time_ter_cond = boost::shared_ptr <terminate_condition>(new timeout_terminate_condition(500));
	 	log_dbg("reactive_servo_task: 6\n");
	 	term_in_left=boost::shared_ptr <terminate_condition>(new terminate_in_left_condition(1.98));
	 	bgVisCond = boost::shared_ptr<begin_condition>(new begin_visible_condition());

	 	v_bhr_1->add_begin_condition(bgVisCond);
	// 	v_bhr_1->add_terminate_condition(time_ter_cond);
	 	v_bhr_1->add_terminate_condition(obj_reach_ter_cond);

	 	v_bhr2->add_begin_condition(bgVisCond);
		v_bhr2->add_terminate_condition(term_in_left);
		log_dbg("reactive_servo_task: 7\n");
	//	start_beh = boost::shared_ptr<behaviour>(new begin_behaviour(*this));
	//	start_beh->add_begin_condition(bgVisCond);

	//	add_behaviour(1, start_beh);
		add_behaviour(1, v_bhr_1);	//dla tego nie chce dzialac!!!
		add_behaviour(2, v_bhr2);	//dla tego powinno dzialac wszystko
		//dla obydwu nie chce dzialac!!! nie czyta z kamery dla drugiej serwowizji

	}
	catch(std::exception& ex)
	{
		sr_ecp_msg->message(lib::FATAL_ERROR, std::string("ERROR in reactive_visual_servo_task: ") + ex.what());
	 	throw ex;
	}
}

reactive_visual_servo_task::~reactive_visual_servo_task()
{
}
task_base* return_created_ecp_task(lib::configurator &config)
{
	return new reactive_visual_servo_task(config);
}

}//task
}
}
}
