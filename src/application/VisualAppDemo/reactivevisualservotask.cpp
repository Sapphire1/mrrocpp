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

	log_client = boost::shared_ptr <logger_client>(new logger_client(500, "127.0.0.1", 7000,"Ellipse_factor;X;Y;Z;alfa;beta;gamma"));
	log_client->set_connect();

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
	 	char config_section_name_arm[] = { "[servovision_arm]" };

	 	reg = boost::shared_ptr <visual_servo_regulator> (new regulator_p(configurator, config_section_name_arm));
	 	ds = boost::shared_ptr <mrrocpp::ecp_mp::sensor::discode::discode_sensor>(new mrrocpp::ecp_mp::sensor::discode::discode_sensor(configurator, config_section_name));
	 	ib_eih_vs = boost::shared_ptr <visual_servo> (new ib_eih_visual_servo(reg, ds, config_section_name, configurator));

	 	log_dbg("reactive_servo_task: 1\n");
	 	// creating behaviours
	 	arm_bh=boost::shared_ptr<behaviour>(new visual_arm_behaviour(*this, config_section_name, log_client, ib_eih_vs));
	 	//wrist_bh=boost::shared_ptr<behaviour>(new visual_wrist_behaviour(*this, config_section_name, log_client));
	 	//start_beh = boost::shared_ptr<behaviour>(new begin_behaviour(*this,log_client));

	 	obj_reach_ter_cond = boost::shared_ptr <terminate_condition>(new object_reached_termination_condition(configurator, config_section_name_arm));
<<<<<<< HEAD
	 	log_dbg("reactive_servo_task: 2\n");

	 	time_ter_cond = boost::shared_ptr <terminate_condition>(new timeout_terminate_condition(5000));
	 	log_dbg("reactive_servo_task: 3\n");
	 	term_in_left=boost::shared_ptr <terminate_condition>(new terminate_in_left_condition(1.98));
	 	term_beg_move=boost::shared_ptr <terminate_condition>(new terminate_beg_pos_condition(1.98));
=======
	 	time_ter_cond = boost::shared_ptr <terminate_condition>(new timeout_terminate_condition(5000));
	 	//term_in_left=boost::shared_ptr <terminate_condition>(new terminate_in_left_condition(1.98));
	 	//term_beg_move=boost::shared_ptr <terminate_condition>(new terminate_beg_pos_condition(1.98));
>>>>>>> 665e0b3c729d9d3602a034405f735bd662842366
	 	term_obj_not_visible=boost::shared_ptr <terminate_condition>(new objectNotVisibleTerminate(configurator, config_section_name_arm));


	 	bgVisCond = boost::shared_ptr<begin_condition>(new begin_visible_condition());
	 	//bgStartPosCond=boost::shared_ptr<begin_condition>(new begin_start_pos_condition());
	 	//bgHybridCond=boost::shared_ptr<begin_condition>(new hybrid_beg_condition());
	 	arm_bh->add_begin_condition(bgVisCond);
	 	arm_bh->add_terminate_condition(time_ter_cond);
	 	arm_bh->add_terminate_condition(term_obj_not_visible);
	 	arm_bh->add_terminate_condition(obj_reach_ter_cond);


	 	//wrist_bh->add_begin_condition(bgHybridCond);
	 	//wrist_bh->add_terminate_condition(term_in_left);
	 	//wrist_bh->add_terminate_condition(term_obj_not_visible);

		//start_beh->add_begin_condition(bgStartPosCond);
		//start_beh->add_terminate_condition(term_beg_move);

		//add_behaviour(1, start_beh);
		add_behaviour(1, arm_bh);
		//add_behaviour(2, wrist_bh);

		log_dbg("reactive_servo_task: end\n");
	}
	catch(std::exception& ex)
	{
		sr_ecp_msg->message(lib::FATAL_ERROR, std::string("ERROR in reactive_visual_servo_task: ") + ex.what());
	 	throw ex;
	}
}

reactive_visual_servo_task::~reactive_visual_servo_task()
{
	log_client->set_disconnect();
}
task_base* return_created_ecp_task(lib::configurator &config)
{
	return new reactive_visual_servo_task(config);
}

}//task
}
}
}
