/*
 * $Id$
 *
 *  Created on: Mar 3, 2013
 *      Author: lzmuda
 */

#include <ctime>
#include <iostream>
#include <fstream>

#include "visual_servo.h"

#include "base/lib/logger.h"

namespace mrrocpp {
namespace ecp {
namespace servovision {

using namespace logger;
using mrrocpp::ecp_mp::sensor::discode::discode_sensor;
using namespace std;

visual_servo::visual_servo(boost::shared_ptr <visual_servo_regulator> regulator, boost::shared_ptr <
		mrrocpp::ecp_mp::sensor::discode::discode_sensor> sensor, const std::string& section_name, mrrocpp::lib::configurator& configurator) :
	regulator(regulator), sensor(sensor), object_visible(true), max_steps_without_reading(3), steps_without_reading(0)
{
	log_dbg("visual_servo::visual_servo() begin\n");

	string log_enabled_name = "vs_log_enabled";
	if (configurator.exists(log_enabled_name, section_name)
			&& configurator.value <bool> (log_enabled_name, section_name)) {
		unsigned int capacity = configurator.value <unsigned int> ("vs_log_capacity", section_name);
		std::string server_addr = configurator.value <std::string> ("vs_log_server_addr", section_name);
		int server_port = configurator.value <int> ("vs_log_server_port", section_name);

		log_client = boost::shared_ptr <logger_client>(new logger_client(capacity, server_addr, server_port, "requestSentTime;sendTime;receiveTime;processingStart;processingEnd;object_visible;np_0_0;np_0_1;np_0_2;np_0_3;np_1_0;np_1_1;np_1_2;np_1_3;np_2_0;np_2_1;np_2_2;np_2_3;error_x;error_y;error_z;error_alpha;error_betha;error_gamma;"));
	}

	log_dbg("visual_servo::visual_servo() end\n");
}

visual_servo::~visual_servo()
{
}

lib::Homog_matrix visual_servo::get_position_change(const lib::Homog_matrix& current_position, double dt)
{
    log_dbg("visual_servo::get_position_change(): begin\n");

	lib::Homog_matrix delta_position;

	struct timespec sendTime, receiveTime, requestSentTime, processingStart, processingEnd;
	sendTime.tv_sec = sendTime.tv_nsec = 0;
	receiveTime.tv_sec = receiveTime.tv_nsec = 0;
	requestSentTime.tv_sec = requestSentTime.tv_nsec = 0;
	processingStart.tv_sec = processingStart.tv_nsec = 0;
	processingEnd.tv_sec = processingEnd.tv_nsec = 0;
	std::cout<<"State "<< sensor->get_state()<<std::endl;
	switch (sensor->get_state())
	{
		case discode_sensor::DSS_READING_RECEIVED: {
			// There's a reading, reset the counter.
			steps_without_reading = 0;

			mrrocpp::ecp_mp::sensor::discode::reading_message_header rmh = sensor->get_rmh();
			sendTime.tv_nsec = rmh.sendTimeNanoseconds;
			sendTime.tv_sec = rmh.sendTimeSeconds;

			receiveTime = sensor->get_reading_received_time();

			requestSentTime = sensor->get_request_sent_time();

			retrieve_reading();
			Types::Mrrocpp_Proxy::Reading* reading = get_reading();

			processingStart.tv_sec = reading->processingStartSeconds;
			processingStart.tv_nsec = reading->processingStartNanoseconds;

			processingEnd.tv_sec = reading->processingEndSeconds;
			processingEnd.tv_nsec = reading->processingEndNanoseconds;
		}
			break;
		case discode_sensor::DSS_CONNECTED: // processing in DisCODe hasn't finished yet
			std::cout<<"discode_sensor::DSS_CONNECTED\n";
			break;
		case discode_sensor::DSS_REQUEST_SENT: // communication or synchronisation in DisCODe took too long
			predict_reading();
			steps_without_reading++;
			break;
		default: // error
			log_dbg("visual_servo::get_position_change(): error\n");
	}

	if (steps_without_reading > max_steps_without_reading)
	{
		std::cout<<"steps_without_reading > max_steps_without_reading\n";
		// The object is no longer visible
		log_dbg("visual_servo::get_position_change(): steps_without_reading > max_steps_without_reading.\n");
		object_visible = false;
	} else
	{
		std::cout<<"steps_without_reading =< max_steps_without_reading\n";
		if(object_visible)
			std::cout<<"object was visible\n";
		object_visible = is_object_visible_in_latest_reading();
	}

	if (object_visible) {
		log_dbg("visual_servo::get_position_change(): object_visible, calling compute_position_change\n");
		delta_position = compute_position_change(current_position, dt);
	} else {
		notify_object_considered_not_visible();
	}

	msg.time_elems = 5;
	msg.time_buf[0] = requestSentTime;
	msg.time_buf[1] = sendTime;
	msg.time_buf[2] = receiveTime;
	msg.time_buf[3] = processingStart;
	msg.time_buf[4] = processingEnd;


	lib::Homog_matrix new_position = current_position * delta_position;

	sprintf(msg.text, "%d;", (int) object_visible);

	msg.append_Homog_matrix(new_position);

	if (object_visible) {
		msg.append_matrix(error);
	}

	// write log message
	if (log_client.get() != NULL) {
		log_client->log(msg);
	}
		log_dbg("visual_servo::get_position_change(): end\n");
	return delta_position;
} // get_position_change

bool visual_servo::is_object_visible()
{
	return object_visible;
}

void visual_servo::reset()
{
	object_visible = false;
}

const Eigen::Matrix <double, 6, 1> & visual_servo::get_error()
{
	return error;
}

boost::shared_ptr <mrrocpp::ecp_mp::sensor::discode::discode_sensor> visual_servo::get_sensor()
{
	return sensor;
}

void visual_servo::notify_object_considered_not_visible()
{
	std::cout<<"visual_servo::notify_object_considered_not_visible\n";
	if(regulator.get() != NULL){
		regulator->reset();
	}
	std::cout<<"visual_servo::notify_object_considered_not_visible end\n";

}

} // namespace servovision
} // namespace ecp
} // namespace mrrocpp
