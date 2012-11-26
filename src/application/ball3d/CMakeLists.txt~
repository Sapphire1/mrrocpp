add_executable(mp_ball3d
	mp_ball3d/mp_t_ball3d.cc
)

target_link_libraries(mp_ball3d mp)

install(TARGETS mp_ball3d DESTINATION bin)



add_executable(ecp_ball3d ecp_ball3d/ecp_t_ball3d.cc 
		generator_ball3d/ecp_g_ball3d.cc
 		CONDITION/condition.cc
		CONDITION/begin_condition.cc
		CONDITION/terminate_condition.cc
		CONDITION/begin_position_condition.cc
		CONDITION/terminate_position_condition.cc
		CONDITION/switch_task2.cc  
)

target_link_libraries(ecp_ball3d 
	${COMMON_LIBRARIES}
	${Boost_PROGRAM_OPTIONS_LIBRARY}
	logger_client
	ecp_robot
)

install(TARGETS	ecp_ball3d DESTINATION bin)

