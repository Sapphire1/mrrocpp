#if !defined(_ECP_GEN_BALL3D_H)
#define _ECP_GEN_BALL3D_H

/*!
 * @file
 * @brief 
 * @author 
 *
 *
 * @ingroup generators
 */

#include "base/ecp/ecp_generator.h"
#include "base/lib/mrmath/mrmath.h"
#include "base/lib/logger_client/logger_client.h"
#include "begin_condition.h"
#include "terminate_condition.h"
#include <vector>
using std::vector;

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {



using logger::logger_client;
using logger::log_message;
/*!
 * @brief 
 *
 * @author
 * @ingroup generators
 */
class behaviour : public common::generator::generator
{
public:
//   dodac liczbe elementow w wektorach warunkow???
  behaviour(common::task::task& _ecp_task);
  virtual ~behaviour();
  void Move();
  void add_begin_condition(boost::shared_ptr <begin_condition> &);
  void add_terminate_condition(boost::shared_ptr <terminate_condition> &);
  std::vector<boost::shared_ptr <begin_condition>> begin_conditions;
  std::vector<boost::shared_ptr <terminate_condition>> terminate_conditions;
  
};


} // namespace generator	
} // namespace common
} // namespace ecp
} // namespace mrrocpp



#endif
