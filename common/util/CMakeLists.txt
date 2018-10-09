project(util)

add_library(util
  string_util.cc
  )

target_include_directories(util
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(util
  ${catkin_LIBRARIES}
)