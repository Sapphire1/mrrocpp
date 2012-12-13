/**
  *  @file reactive_task.h
  *  @brief Class contains reimplemented main_task_algorith method.
  *  @date 2012
  *  @author lzmuda
  */


#ifndef REACTIVE_TASK_H_
#define REACTIVE_TASK_H_

#include "application/visual_servoing_demo/ecp_mp_g_visual_servo_tester.h"
#include <boost/shared_ptr.hpp>
#include "base/ecp/ecp_task.h"
#include "robot/irp6p_m/ecp_r_irp6p_m.h"
#include "robot/irp6ot_m/ecp_r_irp6ot_m.h"
#include "base/lib/logger.h"
#include "behaviour.h"
#include <map>

using namespace mrrocpp::ecp::common::generator;
using namespace mrrocpp::ecp::common::task;
using boost::shared_ptr;
using std::map;

namespace mrrocpp {
namespace ecp {
namespace common {
namespace task {

class reactive_task: public task
{
public:
	/*!
	* @brief Constructor.
	* @param mrrocpp::lib::configurator
	*/
 	reactive_task(mrrocpp::lib::configurator& configurator);
 	/*!
 	* @brief The method sorts all behaviours by the priority, then checks all behaviours, if it can to be execute,
 	* starting from this one with the highest priority.
 	*/
	void main_task_algorithm(void);
	/*!
	* @brief virtual destructor
	*/
	virtual ~reactive_task(){};

protected:
	//! map containing the behaviours and their priorities
 	map<const int, behaviour*> bh_map;
 	//! iterator to the map bh_map
 	map<const int, behaviour*>::iterator it;
 	/*!
 	* @brief The method is responsible for add bahaviours to the reactive_task object.
 	* @param priority
 	* @param pointer to behaviour
 	*/
 	void add_behaviour(int, behaviour*);
};

reactive_task::reactive_task(mrrocpp::lib::configurator& configurator) : common::task::task(configurator){}

void reactive_task::add_behaviour(int prior, behaviour* bh)
{	
 	bh_map.insert(std::pair<char,behaviour*>(prior,bh));
}
void reactive_task::main_task_algorithm(void)
{
	  get_next_state();
	  if (mp_2_ecp_next_state_string == mrrocpp::ecp_mp::generator::ECP_GEN_VISUAL_SERVO_TEST)
	  {
		  while(1)
		  {
			  std::cout<<"main_task_algorithm\n";
			  // for every behaviour
			  for ( it=bh_map.begin() ; it != bh_map.end(); it++ )
			  {
				  // for every begin condition
				  for(int i=0; i<(*it).second->begin_conditions.size(); i++)
				  {	  // check if it can to be execute
					  if((*it).second->begin_conditions[i]->check((*it).second)==true)
					  {
						  std::cout<<"move()\n";
						  (*it).second->Move();
						  (*it).second->begin_conditions[i]->reset();
					  }
				  }//for
			  }//for
		  }//while
	  }//if
	  termination_notice();
}

}//namespace task
}
}
}

#endif /* REACTIVE_TASK_H_ */
