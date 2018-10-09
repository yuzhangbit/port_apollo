project(math)

add_library(math
  sin_table.cc
  angle.cc
  integral.cc
  # geometry
  aabox2d.cc
  box2d.cc
  line_segment2d.cc
  math_utils.cc
  polygon2d.cc
  vec2d.cc
  # cartesian
  cartesian_frenet_conversion.cc
  # path matcher
  #path_matcher.cc
  )

target_include_directories(math
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<INSTALL_INTERFACE:include>
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(math
  ${catkin_LIBRARIES})

catkin_add_gtest(math_tests
  ${CMAKE_SOURCE_DIR}/common_tests.cpp
  vec2d_test.cc
  integral_test.cc
  line_segment2d_test.cc
  cartesian_frenet_conversion_test.cc)

target_link_libraries(math_tests
  ${catkin_LIBRARIES}
  math)
