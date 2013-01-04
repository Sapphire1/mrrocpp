#if !defined(_IN_LEFT_BEHAVIOUR_H)
#define _IN_LEFT_BEHAVIOUR_H

/*!
 * @file
 * @brief 
 * @author 
 *
 *
 * @ingroup generators
 */

#include "behaviour.h"
#include "../VisualApp/visual_servo_regulator_p.h"

using namespace mrrocpp::ecp::servovision;

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {


/*!
 * @brief 
 *
 * @author
 * @ingroup generators
 */
//  in_left_behaviour
//  in_rigth_bahaviour
class in_left_behaviour : public common::generator::behaviour
{
public:
	/**
	 * @brief Constructor
	 * @param _ecp_task ecp task object referencex.
	 */
	Eigen::Matrix <double, 6, 1> actual_position;
	Eigen::Matrix <double, 6, 1> control;
	Eigen::Matrix <double, 6, 1> error;
	boost::shared_ptr <mrrocpp::ecp::servovision::visual_servo_regulator> reg;
	in_left_behaviour(common::task::task& _ecp_task , boost::shared_ptr <mrrocpp::ecp::servovision::visual_servo_regulator> & reg);
	~in_left_behaviour(){};
	/**
	 * @brief generates first step of transition function
	 * @return 
	 */
	bool first_step();
	bool next_step();
};

} // namespace generator
} // namespace common
} // namespace ecp
} // namespace mrrocpp



#endif
