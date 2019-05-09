
set(MATH_SRC
    spiral_curve/cubic_spiral_curve.cc
    spiral_curve/spiral_curve.cc
    spiral_curve/spiral_formula.cc
    spiral_curve/quintic_spiral_curve.cc
    curve_math.cc
    ${PROTO_SRCS}
)

add_library(planning_math ${MATH_SRC})
target_link_libraries(planning_math ${PROTOBUF_LIBRARIES})

catkin_add_gtest(planning_math_tests
    ../planning_tests.cc
    curve_math_test.cc)

target_link_libraries(planning_math_tests
  ${catkin_LIBRARIES}
  planning_math
  ${common_LIBRARIES})
