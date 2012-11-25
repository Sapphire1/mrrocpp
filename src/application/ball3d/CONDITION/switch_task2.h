#ifndef SWITCH_TASK2_H_
#define SWITCH_TASK2_H_

#include <vector>
#include <iostream>
#include "begin_position_condition.h"
#include "terminate_position_condition.h"
#include "base/ecp/ecp_generator.h"
#include "base/lib/mrmath/mrmath.h"

/**
 *	@params wskaznik na obiekt klasy T, wektor wskaznikow na metody klasy T, wektor waunkow poczatkowych, wektor warunkow koncowych
 *	@autor lzmuda
 * 
 */


namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {

template <class T>
class switch_task2
{
public:
    bool terminate;
    bool action;
    int actual, toexec;
    T * g;
    
//  utworzenie wektora skladajacego sie ze wskaznikow do metod klasy T
    typedef void (T::*Type)();
    std::vector<Type> wskz;

//  tworzenie wektorow zawierajacych ograniczenia zaczynajace i konczace ruch
    std::vector<boost::shared_ptr <begin_position_condition>> begin_conditions;
    std::vector<boost::shared_ptr <terminate_position_condition>> terminate_conditions;
    
    switch_task2(T* gen)
    {
        std::cout<<"Konstruktor switch_task2"<<std::endl;
        g=gen;
        actual=0;
    }
    
    void addMethod(Type ptr2Meth)
    {
      wskz.push_back(ptr2Meth);
    }
    
    void addBeginCondition(boost::shared_ptr <begin_position_condition> begptr)
    {
      begin_conditions.push_back(begptr);
    }
    
    void addTerminateCondition(boost::shared_ptr <terminate_position_condition> terptr)
    {
      terminate_conditions.push_back(terptr);
    }
    
    bool execute(lib::Xyz_Angle_Axis_vector & actual_position)
    {
       toexec=wskz.size();
       
//     zakoncz jesli wykonane zostaly wszystkie zadania
       if(actual>=toexec)
          return false;
       std::cout<<"Switch_Task"<<std::endl;
       if(!action)
       {
 	  std::cout<<"Begin Update!!!\n";
//  	  sprawdzamy czy jest warunek i czy mozemy go egzekwowac
  	  action=begin_conditions[actual]->update(actual_position);
 	  std::cout<<"Nie wykonuje zadnego zadania\n";
       }
       if(action)
       {
 	 std::cout<<"Funkcja pracuje\n";
// 	 wywolanie odpowiedniej metody
  	 (g->*wskz[actual])();
       }	
       if(!terminate)
       {
 	  std::cout<<"Terminate Update!\n";
//  	  sprawdzamy czy jest warunek i czy mozemy go egzekwowac
 	  terminate=terminate_conditions[actual]->update(actual_position);
       }
       if(terminate)
       {
 	  std::cout<<"Terminate action\n";
  	  ++actual;
// 	  resetuj flagi jesli kolejne zadanie zostalo zatrzymane
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