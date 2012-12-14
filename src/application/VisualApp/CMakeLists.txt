# add library for visual servoing2
add_library(visual_servoing2
    visual_servo.cc
    visual_servo_regulator.cc
    visual_servo_regulator_p.cc
    visual_servo_regulator_pid.cc
    position_constraint.cc
    cubic_constraint.cc
    behaviour.cc
    ib_eih_visual_servo.cc
    ib_eih_wrist_move.cc
)

# link with discode_sensor
target_link_libraries(visual_servoing2
	discode_sensor
	logger_client
	${COMMON_LIBRARIES}
)

install(TARGETS visual_servoing2 DESTINATION lib)

