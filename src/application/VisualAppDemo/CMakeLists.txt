# object follower - IB - EIH
add_executable(ecp_vsdemo_objectfollower_ib_eih2
    visual_behaviour.cc
    object_reached_termination_condition.cc
    timeout_terminate_condition.cc
    terminate_in_left_condition.cc
    terminate_beg_pos_condition.cc
    beginvisiblecondition.cpp
    hybridbegcondition.cpp
    begin_condition_right.cpp
    begin_start_pos_condition.cc
    GripperNotTwistedBeginCondition.cpp
    reactivevisualservotask.cpp
    begin_behaviour.cc
    visual_arm_behaviour.cc
    visual_wrist_behaviour.cc
    objectNotVisibleTerminate.cpp
)

target_link_libraries(ecp_vsdemo_objectfollower_ib_eih2
	ecp_r_irp6p_m
	ecp_r_irp6ot_m
	visual_servoing2
	ecp ${COMMON_LIBRARIES}
)

####################################
install(TARGETS ecp_vsdemo_objectfollower_ib_eih2 DESTINATION bin)
