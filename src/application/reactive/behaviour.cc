/*!
 * @file
 * @brief 
 * @author lzmuda
 *
 * @ingroup generators
 */

#include "base/ecp/ecp_robot.h"
#include "behaviour.h"
using namespace logger;
using namespace std;


namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {

void behaviour::Move()
{
	bool ex=true;
	// Funkcja ruchu dla ECP
	move_init();
	if (!first_step()) {
		return; // Warunek koncowy spelniony w pierwszym kroku
	}
		// realizacja ruchu
	do {
		if (ecp_t.peek_mp_message()) 
		{
			// END_MOTION received
			break;
		}
			// zlecenie przygotowania danych przez czujniki
		initiate_sensors_readings();
			if (the_robot) 
			{
				// zlecenie ruchu SET oraz odczyt stanu robota GET
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
				// wykonanie kroku ruchu
			if (the_robot->communicate_with_edp) 
			{
					execute_motion();
					the_robot->get_reply();
			}
		}
			// odczytanie danych z wszystkich czujnikow
		get_sensors_readings();
		node_counter++;
		if (ecp_t.pulse_check()) 
		{
			set_trigger();
		}
		// for every terminate condition
		for(int i=0; i<terminate_conditions.size(); i++)
		{  
			if(terminate_conditions[i]->check(this)==false)
			{
				std::cout<<"Termination condition is met!!!\n";
				ex=false;
				break;
			}
		}//for
	
	} while (ex && next_step());
	ecp_t.command.markAsUsed();
}

  behaviour::behaviour(common::task::task& _ecp_task) :	common::generator::generator(_ecp_task){}
  void behaviour::add_begin_condition(boost::shared_ptr <begin_condition> & begptr)
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
