add_executable(reactive
    begin_in_left_condition.cc
    begin_in_right_condition.cc
    terminate_in_left_condition.cc
    terminate_in_right_condition.cc
    reactive_position_task.cc
    behaviour.cc
    in_left_behaviour.cc
    in_right_behaviour.cc
    begin_behaviour.cc
    ../VisualApp/visual_servo_regulator_p.cc
    ../VisualApp/visual_servo_regulator.cc
)

target_link_libraries(reactive
	ecp_r_irp6p_m
	ecp_r_irp6ot_m
	visual_servoing2
	ecp ${COMMON_LIBRARIES}
)

####################################
install(TARGETS reactive DESTINATION bin)
