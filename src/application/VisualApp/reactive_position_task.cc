 /**
  * reactive_position_task.cc
  *
  *  Created on: Dec 3 2012
  *  Author: lzmuda
  */
 
#include "reactive_position_task.h"
#include "robot/irp6p_m/ecp_r_irp6p_m.h"
#include "robot/irp6ot_m/ecp_r_irp6ot_m.h"
#include "in_right_behaviour.h"
#include "in_left_behaviour.h"
#include "begin_in_left_condition.h"
#include "begin_in_right_condition.h"
#include "terminate_in_left_condition.h" 
#include "terminate_in_right_condition.h"

using namespace mrrocpp::ecp::common::generator;
using namespace mrrocpp::ecp::common::task;
 
namespace mrrocpp {
 
namespace ecp {
 
namespace common {
 
namespace task {

reactive_position_task::reactive_position_task(mrrocpp::lib::configurator & configurator) : common::task::reactive_task(configurator)
{
	try{
 		if(config.robot_name == lib::irp6p_m::ROBOT_NAME) 
	{
		ecp_m_robot = (boost::shared_ptr <robot_t>) new irp6p_m::robot(*this);
	} 
	else 
	{
		throw std::runtime_error("Robot not supported");
	}
 		/// create_behaviour
		bhv move_left=bhv(new in_left_behaviour(*this));
  //		bhv move_right=bhv(new in_right_behaviour(*this));
		///TODO
		/// create_begin_cond
 	//	boost::shared_ptr<begin_condition> begLeftCod=boost::shared_ptr<begin_condition>(new begin_in_left_condition);
 	//	boost::shared_ptr<begin_condition> begRightCod=boost::shared_ptr<begin_condition>(new begin_in_right_condition);
 		/// create_ter_cond
 	//	boost::shared_ptr<terminate_condition> terLeftCod=boost::shared_ptr<terminate_condition>(new terminate_in_left_condition);
  	//	boost::shared_ptr<terminate_condition> terRightCod=boost::shared_ptr<terminate_condition>(new terminate_in_right_condition);
 		/// behaviour->add_ter_cond;
 	//	move_left->add_begin_condition(begLeftCod);
 	//	move_right->add_begin_condition(begRightCod);
 		/// behaviour->add_beg_cond
 	//	move_left->add_terminate_condition(terRightCod);
 	//	move_right->add_terminate_condition(terLeftCod);
		/// add_behaviour
 		add_behaviour(1,move_left);
 //		add_behaviour(4,move_right);
		add_behaviour(2,move_left);
// 		add_behaviour(5,move_right);
		add_behaviour(3,move_left);
 	//	add_behaviour(6,move_right);
	}
	catch(std::exception& ex)
	{
		sr_ecp_msg->message(lib::FATAL_ERROR, std::string("ERROR in reactive_position_task: ") + ex.what());
		throw ex;
	} 

  }
 
 task_base* return_created_ecp_task(lib::configurator &config)
 {
 	return new reactive_position_task(config);
 }
 
 } // namespace task
 
 }//namespace common
 
 }//namespace ecp
 
 }//namespace mrrocpp
