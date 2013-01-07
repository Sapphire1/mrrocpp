/*!
 * @file behaviour.cc
 * @brief Implementation of behaviour class
 * @author lzmuda
 * @date 2012
 */

#include "base/ecp/ecp_robot.h"
#include "behaviour.h"
using namespace std;
using namespace mrrocpp::ecp::condition;
namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {

void behaviour::Move()
{
	std::cout<<"Move method\n";
	bool ex=true;
	// Function of motion
	move_init();
	std::cout<<"First step\n";
	if (!first_step()) {
		return; // termination condtion is met
	}
	std::cout<<"After First step\n";
		// implementation of motion
	do {
		if (ecp_t.peek_mp_message()) 
		{
			// END_MOTION received
			break;
		}
		// order to prepare data for sensors
		std::cout<<"initiate sensor readings\n";
		initiate_sensors_readings();
		if (the_robot)
					{
						// set motion order and read the state of a robot-get order
					if (!(ecp_t.continuous_coordination))
					{
						// for data ports purpose
						the_robot->is_new_data = false;
						the_robot->is_new_request = false;
						the_robot->create_command();
						if (the_robot->data_ports_used)
						{
							the_robot->finalize_data_port_command();
						}
					}
						// execution of step motion
					if (the_robot->communicate_with_edp)
					{
							execute_motion();
							the_robot->get_reply();
					}
				}

			// reading data from all sensors
		get_sensors_readings();
		node_counter++;
		if (ecp_t.pulse_check()) 
		{
			set_trigger();
		}
		std::cout<<"Check termination conditions\n";
		// for every termination condition
		for(int i=0; i<terminate_conditions.size(); i++)
		{  	// if condition is met then end Move method
			if(terminate_conditions[i]->check(this)==true)
			{
				std::cout<<"Fulfilled termination condition!\n";
				ex=false;
				break;
			}
			terminate_conditions[i]->reset();
		}//for

	} while (ex && next_step());
	ecp_t.command.markAsUsed();
}

  // constructor
  behaviour::behaviour(common::task::task& _ecp_task) :	common::generator::generator(_ecp_task){}

  void behaviour::add_begin_condition(boost::shared_ptr <begin_condition> &begptr)
  {
	  begin_conditions.push_back(begptr);
  }
  void behaviour::add_terminate_condition(boost::shared_ptr <terminate_condition> & terptr)
  {
      terminate_conditions.push_back(terptr);
  } 

} // namespace generator
} // namespace common
} // namespace ecp
} // namespace mrrocpp
