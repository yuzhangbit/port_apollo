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
  )

target_include_directories(math
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

