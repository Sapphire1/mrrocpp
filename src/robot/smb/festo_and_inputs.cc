/*!
 * \file festo_and_inputs.cc
 * \brief File containing the festo and inputs class methods
 *
 * \author yoyek
 * \date 2011
 *
 */

#include "base/edp/edp_e_motor_driven.h"
#include "const_smb.h"
#include "edp_e_smb.h"
#include "../canopen/gateway_epos_usb.h"
#include "../canopen/gateway_socketcan.h"
#include "../festo/cpv.h"
#include "../maxon/epos.h"
#include "festo_and_inputs.h"
#include "exceptions.h"

namespace mrrocpp {
namespace edp {
namespace smb {

festo_and_inputs::festo_and_inputs(effector &_master) :
		master(_master), epos_di_node(master.epos_di_node), cpv10(master.cpv10), robot_test_mode(master.robot_test_mode)
{
	if (!(robot_test_mode)) {
		festo::U32 DeviceType = cpv10->getDeviceType();
		printf("Device type = 0x%08X\n", DeviceType);

		festo::U8 ErrorRegister = cpv10->getErrorRegister();
		printf("Error register = 0x%02X\n", ErrorRegister);

		festo::U32 ManufacturerStatusRegister = cpv10->getManufacturerStatusRegister();
		printf("Manufacturer status register = 0x%08X\n", ManufacturerStatusRegister);

		uint8_t NumberOfOutputGroups = cpv10->getNumberOf8OutputGroups();
		printf("Number of 8-output groups = %d\n", NumberOfOutputGroups);

		uint8_t Outputs07 = cpv10->getOutputs(1);
		printf("Status of outputs 0..7 = 0x%02x\n", Outputs07);

		master.gateway->SendNMTService(10, canopen::gateway::Start_Remote_Node);

		read_state();
		determine_legs_state();
		desired_output[1] = current_output[1];
		desired_output[2] = current_output[2];

	} else {
		current_legs_state = lib::smb::ALL_UP;
		for (int i = 0; i < lib::smb::LEG_CLAMP_NUMBER; i++) {
			master.edp_ecp_rbuffer.multi_leg_reply.leg[i].is_up = true;
			master.edp_ecp_rbuffer.multi_leg_reply.leg[i].is_down = false;
		}

	}

	next_legs_state = current_legs_state;
}

festo_and_inputs::~festo_and_inputs()
{

}

bool festo_and_inputs::is_checked(int leg_number)
{
	return checked[leg_number - 1];
}

void festo_and_inputs::set_checked(int leg_number)
{
	checked[leg_number - 1] = true;
}

void festo_and_inputs::set_unchecked(int leg_number)
{
	checked[leg_number - 1] = false;
}

void festo_and_inputs::set_all_legs_unchecked()
{
	for (int i = 0; i < lib::smb::LEG_CLAMP_NUMBER; i++) {
		checked[i] = false;
	}
}

bool festo_and_inputs::is_upper_halotron_active(int leg_number)
{
	return epos_inputs[2 * leg_number + 9];
}

bool festo_and_inputs::is_lower_halotron_active(int leg_number)
{
	return epos_inputs[2 * leg_number + 8];
}

bool festo_and_inputs::is_attached(int leg_number)
{
	// to be implemented
	return false;
}

void festo_and_inputs::set_detach(int leg_number, bool value)
{

	// undetachable legs can not be detached !!
	if ((value == true) && (festo_command.undetachable[leg_number - 1] == true)) {
//		master.msg->message("set_detach EMERGENCY return");
		return;
	}
//	master.msg->message("set_detach za  EMERGENCY return");
	switch (leg_number)
	{
		case 1: {
			/*
			 if (value) {
			 master.msg->message("set_detach 1 true");
			 } else {
			 master.msg->message("set_detach 1 false");
			 }
			 */
			desired_output[FESTO_C1_GROUP][FESTO_C1_BIT_TO_SET] = value;
			//std::cout << "set_detach 1 desired_output = " << desired_output[2] << std::endl;

		}

			break;
		case 2: {
			/*
			 if (value) {
			 master.msg->message("set_detach 2 true");
			 } else {
			 master.msg->message("set_detach 2 false");
			 }
			 */
			desired_output[FESTO_C2_GROUP][FESTO_C2_BIT_TO_SET] = value;
			//	std::cout << "set_detach 2 desired_output = " << desired_output[2] << std::endl;
		}

			break;
		case 3: {
			/*
			 if (value) {
			 master.msg->message("set_detach 3 true");
			 } else {
			 master.msg->message("set_detach 3 false");
			 }
			 */
			desired_output[FESTO_C3_GROUP][FESTO_C3_BIT_TO_SET] = value;
			//	std::cout << "set_detach 3 desired_output = " << desired_output[2] << std::endl;

		}

			break;

		default:
			throw NonFatal_error_2(INVALID_MOTION_PARAMETERS);
			break;

	}
}

void festo_and_inputs::set_move_up(int leg_number, bool value)
{
	switch (leg_number)
	{
		case 1: {
			desired_output[FESTO_CY11_GROUP][FESTO_CY11_BIT_TO_SET] = value;
		}

			break;
		case 2: {
			desired_output[FESTO_CY21_GROUP][FESTO_CY21_BIT_TO_SET] = value;
		}

			break;
		case 3: {
			desired_output[FESTO_CY31_GROUP][FESTO_CY31_BIT_TO_SET] = value;
		}

			break;

		default:
			throw NonFatal_error_2(INVALID_MOTION_PARAMETERS);
			break;

	}
}

void festo_and_inputs::set_move_down(int leg_number, bool value)
{
	switch (leg_number)
	{
		case 1: {
			desired_output[FESTO_CY12_GROUP][FESTO_CY12_BIT_TO_SET] = value;
		}

			break;
		case 2: {
			desired_output[FESTO_CY22_GROUP][FESTO_CY22_BIT_TO_SET] = value;
		}

			break;
		case 3: {
			desired_output[FESTO_CY32_GROUP][FESTO_CY32_BIT_TO_SET] = value;
		}

			break;

		default:
			throw NonFatal_error_2(INVALID_MOTION_PARAMETERS);
			break;

	}
}

void festo_and_inputs::set_clean(int leg_number, bool value)
{
	switch (leg_number)
	{
		case 1: {
			//	group_one_desired_output[2] = value;
		}

			break;
		case 2: {

		}

			break;
		case 3: {

		}

			break;

		default:
			throw NonFatal_error_2(INVALID_MOTION_PARAMETERS);
			break;

	}
}

void festo_and_inputs::determine_legs_state()
{
	if (!(robot_test_mode)) {

		int number_of_legs_up = 0;

		for (int i = 0; i < lib::smb::LEG_CLAMP_NUMBER; i++) {

			if (is_upper_halotron_active(i + 1)) {
				number_of_legs_up++;
			}
		}

		switch (number_of_legs_up)
		{
			case 0:

				current_legs_state = lib::smb::ALL_DOWN;
				break;
			case 1:
				current_legs_state = lib::smb::ONE_UP_TWO_DOWN;
				break;
			case 2:
				current_legs_state = lib::smb::TWO_UP_ONE_DOWN;
				break;
			case 3:
				current_legs_state = lib::smb::ALL_UP;
				break;
			default:
				break;

		}

	}
}

/*--------------------------------------------------------------------------*/

void festo_and_inputs::command()
{
	std::stringstream ss(std::stringstream::in | std::stringstream::out);

	master.msg->message("FESTO");

	memcpy(&festo_command, &(master.ecp_edp_cbuffer.festo_command), sizeof(festo_command));

	if (robot_test_mode) {
		ss << festo_command.leg[2];

		master.msg->message(ss.str().c_str());
		// the previous next_legs_state becomes currrent_state

	} else {
		read_state();
		determine_legs_state();
	}

	// determine next_legs_state by counting numebr of legs to be up
	int number_of_legs_up = 0;
	for (int i = 0; i < lib::smb::LEG_CLAMP_NUMBER; i++) {
		if (festo_command.leg[i] == lib::smb::UP) {
			number_of_legs_up++;
		}

	}

	switch (number_of_legs_up)
	{
		case 0:
			next_legs_state = lib::smb::ALL_DOWN;
			break;
		case 1:
			next_legs_state = lib::smb::ONE_UP_TWO_DOWN;
			break;
		case 2:
			next_legs_state = lib::smb::TWO_UP_ONE_DOWN;
			break;
		case 3:
			next_legs_state = lib::smb::ALL_UP;
			break;
		default:
			break;

	}

	// checks if the next_legs_state is valid taking into account current_legs_state
	// and prepares detailed command for festo hardware

	switch (next_legs_state)
	{
		case lib::smb::ALL_DOWN:
			festo_command_all_down();
			break;
		case lib::smb::ONE_UP_TWO_DOWN:
			festo_command_one_up_two_down();
			break;
		case lib::smb::TWO_UP_ONE_DOWN:
			festo_command_two_up_one_down();
			break;
		case lib::smb::ALL_UP:
			festo_command_all_up();
			break;
		default:
			break;

	}

	determine_legs_state();

	if (robot_test_mode) {
		current_legs_state = next_legs_state;
	}

}

void festo_and_inputs::move_one_or_two_down()
{
	// detach all legs that are up to prepare them to go down
	// and put them down

	for (int i = 0; i < lib::smb::LEG_CLAMP_NUMBER; i++) {
		if (is_upper_halotron_active(i + 1)) {
			// DEBUG
			//	if (i != 2) {
			set_move_down(i + 1, true);
			//	} else {
			//		set_move_down(i + 1, false);

			//	}
			set_move_up(i + 1, false);
			set_detach(i + 1, true);
		}
		// for safety reasons
		if (is_lower_halotron_active(i + 1)) {
			set_move_down(i + 1, true);
			set_move_up(i + 1, false);
			set_detach(i + 1, false);
		}

	}
	master.msg->message("move_one_or_two_down przed pierwszym execute_command");
	execute_command();
	master.msg->message("move_one_or_two_down za pierwszym execute_command");
	// waits until all legs go down

	int number_of_legs_down = 0;

	set_all_legs_unchecked();

	for (int iteration = 0; number_of_legs_down < 3; iteration++) {

		//	master.msg->message("wait iteration");
		delay(FAI_SINGLE_DELAY);

		// if it take too long to wait break

		// if (iteration > FAI_DELAY_MAX_ITERATION) {
		// DEBUG
		//	if (iteration > 500) {
		if (iteration > FAI_DELAY_MAX_ITERATION) {
			master.msg->message(lib::NON_FATAL_ERROR, "LEGS MOTION WAIT TIMEOUT");

			break;
		}

		read_state();
		for (int i = 0; i < lib::smb::LEG_CLAMP_NUMBER; i++) {

			if ((!is_checked(i + 1)) && (is_lower_halotron_active(i + 1))) {
				//		std::cout << "move_one_or_two_down 1 desired_output = " << desired_output[2] << std::endl;

				set_checked(i + 1);
				//	std::cout << "move_one_or_two_down 2 desired_output = " << desired_output[2] << std::endl;

				number_of_legs_down++;
				// attach leg
				set_detach(i + 1, false);
				//	std::cout << "move_one_or_two_down 3 desired_output = " << desired_output[2] << std::endl;

				//	master.msg->message("move_one_or_two_down");

			}

		}
	}

	// wait a while in case the legs are still in motion
	delay(500);
	//std::cout << "move_one_or_two_down 4 desired_output = " << desired_output[2] << std::endl;

	// attach legs
	execute_command();
}

void festo_and_inputs::festo_command_all_down()
{
	master.msg->message("festo_command_all_down");
	switch (current_legs_state)
	{
		case lib::smb::ALL_DOWN: {
			BOOST_THROW_EXCEPTION(mrrocpp::edp::smb::nfe_invalid_command_in_given_state() << current_state(current_legs_state) << retrieved_festo_command(lib::smb::ALL_DOWN));
		}
			break;
		case lib::smb::ONE_UP_TWO_DOWN: {
			master.msg->message("ONE_UP_TWO_DOWN");
			if (!festo_test_mode_set_reply(festo_command)) {
				move_one_or_two_down();
			}

		}
			break;
		case lib::smb::TWO_UP_ONE_DOWN: {
			master.msg->message("TWO_UP_ONE_DOWN");
			if (!festo_test_mode_set_reply(festo_command)) {
				move_one_or_two_down();
			}

		}
			break;
		case lib::smb::ALL_UP: {
			master.msg->message("ALL_UP");
			if (!festo_test_mode_set_reply(festo_command)) {

				// moves all legs down and does not detach them !

				for (int i = 0; i < lib::smb::LEG_CLAMP_NUMBER; i++) {
					set_move_down(i + 1, true);
					set_move_up(i + 1, false);
					set_detach(i + 1, false);
				}

				execute_command();

				// waits until all legs are in down position
				int number_of_legs_down = 0;

				set_all_legs_unchecked();

				for (int iteration = 0; number_of_legs_down < 3; iteration++) {

					delay(FAI_SINGLE_DELAY);

					// if it take too long to wait break
					if (iteration > FAI_DELAY_MAX_ITERATION) {
						master.msg->message(lib::NON_FATAL_ERROR, "LEGS MOTION WAIT TIMEOUT");

						break;
					}

					read_state();

					for (int i = 0; i < lib::smb::LEG_CLAMP_NUMBER; i++) {

						if ((!is_checked(i + 1)) && (is_lower_halotron_active(i + 1))) {
							set_checked(i + 1);
							number_of_legs_down++;
						}

					}
				}
			}
		}
			break;
		default:
			break;

	}
}

void festo_and_inputs::festo_command_one_up_two_down()
{
	BOOST_THROW_EXCEPTION(mrrocpp::edp::smb::nfe_invalid_command_in_given_state()<<current_state(current_legs_state) << retrieved_festo_command(lib::smb::ONE_UP_TWO_DOWN));
}

void festo_and_inputs::festo_command_two_up_one_down()
{
	switch (current_legs_state)
	{
		case lib::smb::ALL_DOWN: {
			if (!festo_test_mode_set_reply(festo_command)) {

				// odlacz te nogi ktore maja zostac podniesione

				for (int i = 0; i < lib::smb::LEG_CLAMP_NUMBER; i++) {
					if (festo_command.leg[i] == lib::smb::UP) {
						if (is_lower_halotron_active(i + 1)) {
							set_detach(i + 1, true);
							set_move_down(i + 1, false);
						}
					}
				}
				execute_command();
				//odczekaj pewien czas liczac na to ze zaciski odpuszcza
				delay(1000);
				// podnos nogi
				for (int i = 0; i < lib::smb::LEG_CLAMP_NUMBER; i++) {
					if (festo_command.leg[i] == lib::smb::UP) {
						if (is_lower_halotron_active(i + 1)) {
							set_move_up(i + 1, true);
						}
					}
				}
				execute_command();

				// czekaj az sie uniosa
				int number_of_legs_up = 0;

				set_all_legs_unchecked();

				for (int iteration = 0; number_of_legs_up < 2; iteration++) {
					delay(FAI_SINGLE_DELAY);

					// if it take too long to wait break
					if (iteration > FAI_DELAY_MAX_ITERATION) {
						master.msg->message(lib::NON_FATAL_ERROR, "LEGS MOTION WAIT TIMEOUT");

						break;
					}

					read_state();
					for (int i = 0; i < lib::smb::LEG_CLAMP_NUMBER; i++) {
						if ((!is_checked(i + 1)) && (is_upper_halotron_active(i + 1))
								&& (festo_command.leg[i] == lib::smb::UP)) {
							set_checked(i + 1);
							number_of_legs_up++;
							set_detach(i + 1, false);
						}
					}
				}

				execute_command();
			}
		}

			break;
		case lib::smb::ONE_UP_TWO_DOWN:
		case lib::smb::TWO_UP_ONE_DOWN:
		case lib::smb::ALL_UP: {
			BOOST_THROW_EXCEPTION(mrrocpp::edp::smb::nfe_invalid_command_in_given_state()<<current_state(current_legs_state) << retrieved_festo_command(lib::smb::TWO_UP_ONE_DOWN));
		}
			break;
		default:
			break;

	}
}

void festo_and_inputs::festo_command_all_up()
{
	switch (current_legs_state)
	{
		case lib::smb::ALL_DOWN: {
			if (!festo_test_mode_set_reply(festo_command)) {

				// move all legs up and do not detach them;

				for (int i = 0; i < lib::smb::LEG_CLAMP_NUMBER; i++) {
					set_move_down(i + 1, false);
					set_move_up(i + 1, true);
				}

				execute_command();

				// waits until all legs are in upper position

				int number_of_legs_up = 0;

				set_all_legs_unchecked();

				//	master.msg->message("festo_command_all_up before wait");

				for (int iteration = 0; number_of_legs_up < 3; iteration++) {

					delay(FAI_SINGLE_DELAY);

					// if it take too long to wait break
					if (iteration > FAI_DELAY_MAX_ITERATION) {
						master.msg->message(lib::NON_FATAL_ERROR, "LEGS MOTION WAIT TIMEOUT");

						break;
					}

					read_state();
					//master.msg->message("festo_command_all_up iteration");
					for (int i = 0; i < lib::smb::LEG_CLAMP_NUMBER; i++) {

						if ((!is_checked(i + 1)) && (is_upper_halotron_active(i + 1))) {
							set_checked(i + 1);
							number_of_legs_up++;
							//		master.msg->message("festo_command_all_up is_checked");
						}

					}
				}
			}
		}

			break;
		case lib::smb::ONE_UP_TWO_DOWN:
		case lib::smb::TWO_UP_ONE_DOWN:
		case lib::smb::ALL_UP:
			BOOST_THROW_EXCEPTION(mrrocpp::edp::smb::nfe_invalid_command_in_given_state()<<current_state(current_legs_state) << retrieved_festo_command(lib::smb::ALL_UP));
			break;
		default:
			break;

	}
}

bool festo_and_inputs::festo_test_mode_set_reply(lib::smb::festo_command_td& festo_command)
{
	if (robot_test_mode) {
		for (int i = 0; i < lib::smb::LEG_CLAMP_NUMBER; i++) {
			if (festo_command.leg[i] == lib::smb::UP) {
				master.edp_ecp_rbuffer.multi_leg_reply.leg[i].is_up = true;
				master.edp_ecp_rbuffer.multi_leg_reply.leg[i].is_down = false;
			} else {
				master.edp_ecp_rbuffer.multi_leg_reply.leg[i].is_up = false;
				master.edp_ecp_rbuffer.multi_leg_reply.leg[i].is_down = true;
			}

		}
	}
	return robot_test_mode;
}

void festo_and_inputs::read_state()
{
	if (!(robot_test_mode)) {
		epos_inputs = epos_di_node->getDInput();

		current_output[1] = cpv10->getOutputs(1);
		// desired_output[1] = current_output[1];
		//	std::cout << "group_one_desired_output 1= " << group_one_desired_output << std::endl;
		current_output[2] = cpv10->getOutputs(2);
		//	std::cout << "group_two_current_output 1= " << group_two_current_output << std::endl;
		//	desired_output[2] = current_output[2];
	}
}

void festo_and_inputs::create_reply()
{

	determine_legs_state();

	if (!robot_test_mode) {
		read_state();
		for (int i = 0; i < lib::smb::LEG_CLAMP_NUMBER; i++) {
			master.edp_ecp_rbuffer.multi_leg_reply.leg[i].is_down = is_lower_halotron_active(i + 1);
			master.edp_ecp_rbuffer.multi_leg_reply.leg[i].is_up = is_upper_halotron_active(i + 1);
			master.edp_ecp_rbuffer.multi_leg_reply.leg[i].is_attached = is_attached(i + 1);
		}
		//std::cout << "epos digital inputs = " << epos_digits << std::endl;
	}
}

void festo_and_inputs::execute_command()
{
	if (!robot_test_mode) {
		cpv10->setOutputs(1, (uint8_t) desired_output[1].to_ulong());
		cpv10->setOutputs(2, (uint8_t) desired_output[2].to_ulong());
		//	std::cout << "desired_output = " << desired_output[2] << std::endl;
		read_state();
		desired_output[1] = current_output[1];
		desired_output[2] = current_output[2];

	}
}

} // namespace smb
} // namespace edp
} // namespace mrrocpp
