#include "condition.h"

// 2 zmienne globalne
///TODO
///poprawic to!
bool condition::any_begin_condition_met;
bool condition::any_terminate_condition_met;

bool condition::get_any_begin_condition(){return any_begin_condition_met;}
void condition::set_any_terminate_condition(bool any_cond){any_terminate_condition_met=any_cond;}
bool condition::get_any_terminate_condition(){return any_terminate_condition_met;}
void condition::set_any_begin_condition(bool any_cond){any_begin_condition_met=any_cond;}
