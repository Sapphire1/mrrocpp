/*
 * ecp_t_objectfollower_ib_eih.h
 *
 *  Created on: Apr 21, 2010
 *      Author: mboryn
 */

#ifndef ECP_T_OBJECTFOLLOWER_IB_EIH_H_
#define ECP_T_OBJECTFOLLOWER_IB_EIH_H_

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

/** @addtogroup servovision
 *  @{
 */

/**
 *
 */

class reactive_task: public task
{
public:
 	reactive_task(mrrocpp::lib::configurator& configurator);

	void main_task_algorithm(void);
	virtual ~reactive_task(){};

protected:
 	map<const int, behaviour*> bh_map;
	map<const int, behaviour*>::iterator it;
 	void add_behaviour(int, behaviour*);

};

reactive_task::reactive_task(mrrocpp::lib::configurator& configurator) : common::task::task(configurator)
{
// jak nie bedzie zdefiniowane to bedzie krzyczal przy starcie MP
// std::string robot_name = config.value<std::string>("robot_name", "[visualservo_tester]");
	
}

void reactive_task::add_behaviour(int prior, behaviour * bh)
{	
 	bh_map.insert ( std::pair<char,behaviour*>(prior,bh));
}

void reactive_task::main_task_algorithm(void)
{
	  get_next_state();
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
				  }
			  }//for
		  }//for
	  }//while
	  termination_notice();
}

/** @} */

}//namespace task

}

}

}

#endif /* ECP_T_OBJECTFOLLOWER_IB_EIH_H_ */
