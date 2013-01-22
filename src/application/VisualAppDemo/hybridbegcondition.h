/*
 * hybridbegcondition.h
 *
 *  Created on: 22-01-2013
 *      Author: lzmuda
 */

#ifndef HYBRIDBEGCONDITION_H_
#define HYBRIDBEGCONDITION_H_

#include "../VisualApp/begin_condition.h"
#include "../VisualAppDemo/visual_behaviour.h"
#include "base/ecp/ecp_robot.h"
#include "base/ecp/ecp_generator.h"

namespace mrrocpp {
namespace ecp {
namespace condition {


class hybrid_beg_condition : public begin_condition{
public:
	hybrid_beg_condition();
	virtual ~hybrid_beg_condition();
	bool check(const boost::shared_ptr<mrrocpp::ecp::common::generator::behaviour> &);
	void reset(){;}
};




} /* namespace condition */
} /* namespace ecp */
} /* namespace mrrocpp */
#endif /* HYBRIDBEGCONDITION_H_ */
