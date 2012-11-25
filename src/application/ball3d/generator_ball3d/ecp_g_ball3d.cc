/*!
 * @file
 * @brief 
 * @author lzmuda
 *
 * @ingroup generators
 */

#include "base/ecp/ecp_robot.h"
#include "ecp_g_ball3d.h"
using namespace logger;
using namespace std;

// w miejsce tych funkcji podstawic swoje wlasne

// pamietac o tym, ze ja musze szybko niwelowac uchyb wiec dt=steps*time_of_step
// gdzies bylo, ze time of step to 0.002 wiec podobny mam miec chyba dt
// zeby od razu mi niwelowalo

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {


lib::Xyz_Angle_Axis_vector tool_vector;
boost::shared_ptr <switch_task2<ball3d>> sch_tsk2;

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // ///////////////////
//
// 			ball3d generator
//
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // ///////////////////

ball3d::ball3d(common::task::task& _ecp_task) :	common::generator::generator(_ecp_task)
{
	generator_name = ecp_mp::generator::ECP_GEN_BALL3D;
}

bool ball3d::first_step()
{	
	std::vector<lala> wskazniki;
	
	std::vector<double> left_begin_limit(2);
	left_begin_limit[0]=1.8;
	left_begin_limit[1]=2.2;
	
	std::vector<double> right_begin_limit(2);
	right_begin_limit[0]=1.6;
	right_begin_limit[1]=1.8;
	
	boost::shared_ptr <begin_position_condition> in_left=boost::shared_ptr<begin_position_condition>(new begin_position_condition(left_begin_limit));
	boost::shared_ptr <begin_position_condition> in_right=in_right=boost::shared_ptr<begin_position_condition>(new begin_position_condition(right_begin_limit));
	
// 	skorzystac tutaj z enum
	int left_opt=1;
	int right_opt=2;
	
	boost::shared_ptr <terminate_position_condition>  terminate_in_left=boost::shared_ptr<terminate_position_condition>(new terminate_position_condition(1.7, left_opt));
	boost::shared_ptr <terminate_position_condition>  terminate_in_right=boost::shared_ptr<terminate_position_condition>(new terminate_position_condition(2.2,right_opt));
		
	// stworzenie obiektu przelaczajacego zadania
 	sch_tsk2 = boost::shared_ptr<switch_task2<ball3d>>(new switch_task2<ball3d>(this/*, wskazniki, bpc_vcr,tpc_vcr*/));
	
	// Dodanie metod i warunkow do obiektu przelaczajacego zadania
	sch_tsk2->addMethod(&ball3d::move_left);
	sch_tsk2->addMethod(&ball3d::move_right);
	
	sch_tsk2->addBeginCondition(in_left);	
	sch_tsk2->addBeginCondition(in_right);
	
	sch_tsk2->addTerminateCondition(terminate_in_left);
	sch_tsk2->addTerminateCondition(terminate_in_right);
	
	log = boost::shared_ptr <logger_client>(new logger_client(500, "localhost", 7000, "np_0_0;np_0_1;np_0_2;np_0_3;np_1_0;np_1_1;np_1_2;np_1_3;np_2_0;np_2_1;np_2_2;np_2_3","lukaszowe"));
 	log->set_connect();
	
	counter=0;
 	int step_no=10;

	lib::Homog_matrix tool_frame(0.0, 0.0, 0.0);
	the_robot->ecp_command.robot_model.tool_frame_def.tool_frame = tool_frame;

	the_robot->ecp_command.instruction_type = lib::GET;
	the_robot->ecp_command.get_type = ARM_DEFINITION; // arm - ORYGINAL
	the_robot->ecp_command.set_type = ARM_DEFINITION | ROBOT_MODEL_DEFINITION;
	//	the_robot->ecp_command.set_type = ARM_DEFINITION;
	the_robot->ecp_command.robot_model.type = lib::TOOL_FRAME;
	the_robot->ecp_command.get_robot_model_type = lib::TOOL_FRAME;
	the_robot->ecp_command.set_arm_type = lib::PF_VELOCITY;
//	the_robot->ecp_command.get_arm_type = lib::FRAME;
	the_robot->ecp_command.motion_type = lib::ABSOLUTE;
	the_robot->ecp_command.interpolation_type = lib::TCIM;
	the_robot->ecp_command.motion_steps = step_no;
	the_robot->ecp_command.value_in_step_no = step_no - 2;
	
 	for (int i = 0; i < 6; i++) 
	{
		the_robot->ecp_command.arm.pf_def.force_xyz_torque_xyz[i] = 0.5;
	}
  

	return true;
}
bool ball3d::next_step()
{		
	  bool run=true;
	  
	  double current_position[6];
	  lib::Homog_matrix tmp=the_robot->reply_package.arm.pf_def.arm_frame;
	  log_message  msg;
	  
	  msg.append_Homog_matrix(tmp);
	  tmp.get_xyz_angle_axis(tool_vector);
	  tool_vector.to_table(current_position);
 	
	  std::cout << "Aktualna: "<<current_position[0]<<" + uchyb: "<< 0.2*sin(counter*3.14/50)<<
	  "= " << current_position[0]+ 0.2*sin(counter*3.14/50) << std::endl;
	  log->log(msg);
	  
  	  run=sch_tsk2->execute(tool_vector);
	  
	  if(!run)
	  {
	      log->set_disconnect();
  	      return run;
	  }
	  return run;
}

void ball3d::make_circle()
{
 
	the_robot->ecp_command.arm.pf_def.arm_coordinates[0] = 0.2* (sin(counter*3.14/50)); 
	the_robot->ecp_command.arm.pf_def.arm_coordinates[1] = 0.2* (cos(counter*3.14/50)); // -0.1 lewo dols
	the_robot->ecp_command.arm.pf_def.arm_coordinates[2] = 0; //-0.1 prawo troche do gory
	the_robot->ecp_command.arm.pf_def.arm_coordinates[3] = 0; // -0.1 kamera (rekojesc) do tyłu
	the_robot->ecp_command.arm.pf_def.arm_coordinates[4] = 0; //-0.1 kręci się w prawo
	the_robot->ecp_command.arm.pf_def.arm_coordinates[5] = 0; // -0.1 prawo do przodu
	counter++;
	std::cout<< "Next_STEP \n"<<std::endl;
	std::cout<<"Counter: "<<counter <<std::endl;
	the_robot->ecp_command.instruction_type = lib::SET_GET;

	// Obliczenie zadanej pozycji posredniej w tym kroku ruchu
	 
	lib::Homog_matrix current_frame_wo_offset(the_robot->reply_package.arm.pf_def.arm_frame);
	current_frame_wo_offset.remove_translation();

	lib::Ft_v_vector force_torque(the_robot->reply_package.arm.pf_def.force_xyz_torque_xyz);
	
	
}
void ball3d::move_left()
{
  
  
	the_robot->ecp_command.instruction_type = lib::GET;
	the_robot->ecp_command.get_type = ARM_DEFINITION;
	the_robot->ecp_command.set_type = ARM_DEFINITION;
	the_robot->ecp_command.set_arm_type = lib::FRAME;
	the_robot->ecp_command.motion_type = lib::RELATIVE;
	the_robot->ecp_command.interpolation_type = lib::MIM;
 	the_robot->ecp_command.motion_steps = 100;
 	the_robot->ecp_command.value_in_step_no = 97;
	
	
	lib::Homog_matrix homog_matrix;
	double nextChange[6];
	the_robot->ecp_command.instruction_type = lib::SET_GET;
	nextChange[0]=0;
	nextChange[1]=0.02;
	nextChange[2]=0;
	nextChange[3]=0;
	nextChange[4]=0;
	nextChange[5]=0;
	homog_matrix.set_from_xyz_angle_axis(lib::Xyz_Angle_Axis_vector(nextChange[0], nextChange[1], nextChange[2], nextChange[3], nextChange[4], nextChange[5]));

	the_robot->ecp_command.arm.pf_def.arm_frame = homog_matrix;
	the_robot->ecp_command.instruction_type = lib::SET_GET;

	// Obliczenie zadanej pozycji posredniej w tym kroku ruchu
	 
	lib::Homog_matrix current_frame_wo_offset(the_robot->reply_package.arm.pf_def.arm_frame);
	current_frame_wo_offset.remove_translation();

	lib::Ft_v_vector force_torque(the_robot->reply_package.arm.pf_def.force_xyz_torque_xyz);
	counter++;
	std::cout<< "Next_STEP \n"<<std::endl;
	std::cout<<"Counter: "<<counter <<std::endl;


}

void ball3d::move_right()
{
  
  
	the_robot->ecp_command.instruction_type = lib::GET;
	the_robot->ecp_command.get_type = ARM_DEFINITION;
	the_robot->ecp_command.set_type = ARM_DEFINITION;
	the_robot->ecp_command.set_arm_type = lib::FRAME;
	the_robot->ecp_command.motion_type = lib::RELATIVE;
	the_robot->ecp_command.interpolation_type = lib::MIM;
 	the_robot->ecp_command.motion_steps = 100;
 	the_robot->ecp_command.value_in_step_no = 97;
	
	
	lib::Homog_matrix homog_matrix;
	double nextChange[6];
	the_robot->ecp_command.instruction_type = lib::SET_GET;
	nextChange[0]=0;
	nextChange[1]=-0.02;
	nextChange[2]=0;
	nextChange[3]=0;
	nextChange[4]=0;
	nextChange[5]=0;
	homog_matrix.set_from_xyz_angle_axis(lib::Xyz_Angle_Axis_vector(nextChange[0], nextChange[1], nextChange[2], nextChange[3], nextChange[4], nextChange[5]));

	the_robot->ecp_command.arm.pf_def.arm_frame = homog_matrix;
	the_robot->ecp_command.instruction_type = lib::SET_GET;

	// Obliczenie zadanej pozycji posredniej w tym kroku ruchu
	 
	lib::Homog_matrix current_frame_wo_offset(the_robot->reply_package.arm.pf_def.arm_frame);
	current_frame_wo_offset.remove_translation();

	lib::Ft_v_vector force_torque(the_robot->reply_package.arm.pf_def.force_xyz_torque_xyz);
	counter++;
	std::cout<< "Next_STEP \n"<<std::endl;
	std::cout<<"Counter: "<<counter <<std::endl;


}
} // namespace generator
} // namespace common
} // namespace ecp
} // namespace mrrocpp
