/**
 *  @file visual_behaviour.h
 *  @date 2013
 *  @author lzmuda
 */


#ifndef VISUAL_BEHAVIOUR_H_
#define VISUAL_BEHAVIOUR_H_

#include <vector>
#include <boost/shared_ptr.hpp>
#include <string>

#include "base/ecp/ecp_generator.h"
#include "application/VisualApp/visual_servo.h"
#include "application/VisualApp/position_constraint.h"
#include "application/VisualApp/terminate_condition.h"
#include "base/lib/logger_client/logger_client.h"
#include "application/VisualApp/behaviour.h"
#include "application/VisualApp/visual_servo_regulator_p.h"
#include "application/VisualApp/visual_servo.h"
#include <csignal>
#include <ctime>
#include <sstream>

namespace mrrocpp {

namespace ecp {

namespace servovision {
class termination_condition;
}

namespace common {

namespace generator {

/** @defgroup servovision Visual servoing
* @ingroup application
* @{
*/

/**
* Base generator for all visual servo managers.
* Servo manager is a generator that takes control calculated in multiple visual_servo objects and aggregates them.
* It also applies constraints for end effector speed, acceleration and position.
*/
class visual_behaviour: public behaviour
{
public:
boost::shared_ptr <mrrocpp::ecp::servovision::visual_servo_regulator> reg;
boost::shared_ptr <mrrocpp::ecp_mp::sensor::discode::discode_sensor> ds;
boost::shared_ptr <mrrocpp::ecp::servovision::visual_servo>  vs;
boost::shared_ptr<logger::logger_client> log_client;
logger::log_message msg;
static bool sensor_configured;
visual_behaviour(mrrocpp::ecp::common::task::task & ecp_task, const char * section_name);
~visual_behaviour();
bool first_step();
bool next_step();

/** Configures all servos.
* Calls configure_all_servos() of derived class and then for all sensors calls configure_sensor().
* After that updates sensor map
*/
void configure(const std::string & sensor_prefix = "VSM_SENSOR_");
lib::Homog_matrix get_aggregated_position_change();
/**
* Add position constraint.
* At least one position constraint must be met to move end effector.
* If there are no position constraints, end effector position will be unconstrained,
* so it is likely to move end effector beyond it's limits.
* @param new_constraint
*/
void add_position_constraint(boost::shared_ptr <mrrocpp::ecp::servovision::position_constraint> new_constraint);

/**
* Add termination condition.
* Every next_step() all termination conditions are updated and checked. If at least one of them
* is met, next_step() will return false and generator will terminate.
* If there are no termination conditions, generator will never stop.
* @param term_cond
*/


void update_motion_steps(ecp_mp::sensor::discode::reading_message_header rmh);


/**
* Get linear end effector's speed.
* @return
*/
double get_linear_speed() const;
/**
* Get angular end effector's speed.
* @return
*/
double get_angular_speed() const;
/**
* Get linear end effector's acceleration.
* @return
*/
double get_linear_acceleration() const;
/**
* Get angular end effector's acceleration.
* @return
*/
double get_angular_acceleration() const;

/**
* Get all visual servos.
* @return
*/
const boost::shared_ptr <mrrocpp::ecp::servovision::visual_servo> & get_servo() const;

const lib::Homog_matrix& get_current_position() const;

protected:

/**
* Called in next_step() to get aggregated control to pass to EDP.
* @return
*/

/**
* Called from constructor to initialize all servos. After this call, servos field must be initialized.
*/
protected:
/** Time for single step () */

static const double step_time;
double image_sampling_period;
bool macrostep_length_control;


double get_dt() const;
void set_new_motion_steps(int new_motion_steps);
int get_new_motion_steps() const;
int get_motion_steps() const;
int get_motion_steps_base() const;

private:
  
	
/** Default number of steps for macrostep. */
static const int motion_steps_default;
static const int motion_steps_min;
static const int motion_steps_max;
int value_in_step_no;

/** Number of steps for macrostep.
* If present, this value is read from config, otherwise is set to motion_steps_default
*/
int motion_steps;

int motion_steps_base;

int new_motion_steps;

/** Time between next_step() calls */
double dt;

lib::Homog_matrix current_position;
bool current_position_saved;

std::vector <boost::shared_ptr <servovision::position_constraint> > position_constraints;
std::vector <boost::shared_ptr <servovision::termination_condition> > termination_conditions;

/** End effector's linear speed */
double max_speed;
/** End effector's rotation speed */
double max_angular_speed;

/** End effector's linear acceleration */
double max_acceleration;
/** End effector's rotation acceleration */
double max_angular_acceleration;

/** Current end effector speed */
Eigen::Matrix <double, 3, 1> velocity;
/** Current end effector speed */
Eigen::Matrix <double, 3, 1> angular_velocity;

/** Previous end effector speed */
Eigen::Matrix <double, 3, 1> prev_velocity;
/** Previous end effector speed */
Eigen::Matrix <double, 3, 1> prev_angular_velocity;

/** End effector acceleration */
Eigen::Matrix <double, 3, 1> acceleration;
/** End effector acceleration */
Eigen::Matrix <double, 3, 1> angular_acceleration;

/** Set to true, if speed/accel was constrained by constrain_speed_accel() */
bool is_linear_speed_constrained;

/** Set to true, if speed/accel was constrained by constrain_speed_accel() */
bool is_linear_accel_constrained;

/** Set to true, if speed/accel was constrained by constrain_speed_accel() */
bool is_angular_speed_constrained;

/** Set to true, if speed/accel was constrained by constrain_speed_accel() */
bool is_angular_accel_constrained;

bool speed_constrained, accel_constrained;

/** Set to true, if position was constrained by constrain_position() */
bool is_position_constrained;


void constrain_position(lib::Homog_matrix & new_position);

/**
* Apply constraints for velocity and acceleration on single 3 element vector.
* @param ds
* @param prev_v
* @param v
* @param a
* @param max_v
* @param max_a
*/
void constrain_vector(Eigen::Matrix <double, 3, 1> &ds, Eigen::Matrix <double, 3, 1> &prev_v, Eigen::Matrix <
double, 3, 1> &v, Eigen::Matrix <double, 3, 1> &a, double max_v, double max_a);

/**
* Apply constraints for velocity and acceleration, both linear and angular.
* @param position_change
*/
void constrain_speed_accel(lib::Homog_matrix & position_change);

};

/** @} */

} // namespace generator

} // namespace common

} // namespace ecp

} // namespace mrrocpp

#endif /* VISUAL_SERVO_MANAGER_H_ */
