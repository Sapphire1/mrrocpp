/*!
 * @file switch_task.h
 * @brief File containing the declaration of switch_task class
 * 
 * @author Lukasz Zmuda
 * @date 2012
 */

#ifndef SWITCH_TASK_H_
#define SWITCH_TASK_H_

#include <vector>
#include <iostream>
#include "begin_position_condition.h"
#include "terminate_position_condition.h"
#include "base/ecp/ecp_generator.h"
#include "base/lib/mrmath/mrmath.h"

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {

/*!
 * @brief Class is responsible for switching executing tasks of object T 
 */
template <class T>
class switch_task2
{
 /*!
 * @brief Flag indicate whether the method is active or not.
 */
    bool terminate;
/*!
 * @brief Flag indicate whether the method is terminate or not.
 */
    bool action;
 /*!
 * @brief Counter to the current method.
 */
    int actual; 
/*!
 * @brief Numbers of methods to perform.
 */
    int toexec;
 /*!
 * @brief Object's pointer.
 */
    T * g;
 /*!
 * @brief Vector including pointers to object methods.
 */
    typedef void (T::*Type)();
    std::vector<Type> wskz;
 /*!
 * @brief Vectors contains references to begin and terminate conditions.
 */
    std::vector<boost::shared_ptr <begin_position_condition>> begin_conditions;
    std::vector<boost::shared_ptr <terminate_position_condition>> terminate_conditions;
public:
 /*!
 * @brief Constructor
 * @param Pointer to an object of type T.
 */
    switch_task2(T* gen)
    {
        std::cout<<"Konstruktor switch_task"<<std::endl;
        g=gen;
        actual=0;
    }
 /*!
 * @brief Adding pointers to methods of class T.
 * @param Pointer to an object of type T.
 */
    void addMethod(Type ptr2Meth)
    {
      wskz.push_back(ptr2Meth);
    }
    
/*!
 * @brief Adding references to begin conditions.
 * @param Reference to a begin position.
 */
    void addBeginCondition(boost::shared_ptr <begin_position_condition> begptr)
    {
      begin_conditions.push_back(begptr);
    }
/*!
 * @brief Adding references to terminate conditions.
 * @param Reference to a terminate position.
 */
    void addTerminateCondition(boost::shared_ptr <terminate_position_condition> terptr)
    {
      terminate_conditions.push_back(terptr);
    }

/*!
 * @brief Method to perform all tasks
 * @param false when all tasks have been completed otherwise return true
 */
    bool execute(lib::Xyz_Angle_Axis_vector & actual_position)
    {
       toexec=wskz.size();
       if(actual>=toexec)
          return false;
       if(!action)
       {
  	  action=begin_conditions[actual]->update(actual_position);
       }
       if(action)
       {
  	 (g->*wskz[actual])();
       }	
       if(!terminate)
       {
 	  terminate=terminate_conditions[actual]->update(actual_position);
       }
       if(terminate)
       {
  	  ++actual;
  	  action=false;
	  terminate=false;
       }
       return true;
  }
};

} // namespace generator
} // namespace common
} // namespace ecp
} // namespace mrrocpp
#endif