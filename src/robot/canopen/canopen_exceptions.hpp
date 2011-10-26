/*
 * canopen_exceptions.hpp
 *
 *  Created on: 19-10-2011
 *      Author: tkornuta
 */

#ifndef CANOPEN_EXCEPTIONS_HPP_
#define CANOPEN_EXCEPTIONS_HPP_

#include "base/lib/exception.h"

namespace mrrocpp {
namespace edp {
namespace canopen {

/*!
 * \brief All high-level methods throws this exception in case of error.
 * \author ptrojane/tkornuta
 */
REGISTER_SYSTEM_ERROR(se_canopen_error, "CANopen Error")


//! reason of an exception
typedef boost::error_info <struct tag_reason, std::string> reason;

//! index of the CANOpen object
typedef boost::error_info <struct tag_index, uint16_t> dictionary_index;

//! subindex of the CANOpen object
typedef boost::error_info <struct tag_subindex, uint8_t> dictionary_subindex;

//! CAN ID
typedef boost::error_info <struct tag_canId, uint8_t> canId;

//! errno code of a failed system call
typedef boost::error_info <struct tag_errno_code, int> errno_code;

//! failed system call
typedef boost::error_info <struct tag_errno_code, std::string> errno_call;

} /* namespace epos */
} /* namespace edp */
} /* namespace mrrocpp */

#endif /* CANOPEN_EXCEPTIONS_HPP_ */
