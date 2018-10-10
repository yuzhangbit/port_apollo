cmake_minimum_required(VERSION 3.0)
project(common VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

set(CATKIN_ENABLE_TESTING ON)

# for the Protobuf
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

set(PKG_DEPS
  glog_catkin)

find_package(catkin REQUIRED COMPONENTS ${PKG_DEPS})
find_package(Protobuf REQUIRED)

set(PROTO_DEFNS
  proto/pnc_point.proto
  proto/error_code.proto)

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${PROTO_DEFNS})

include_directories(include
  "."
  ${CMAKE_CURRENT_BINARY_DIR}
  ${catkin_INCLUDE_DIRS}
  ${PROTOBUF_INCLUDE_DIRS}
)

catkin_package(
  INCLUDE_DIRS ${CATKIN_DEVEL_PREFIX}/include include
  LIBRARIES common
  CATKIN_DEPENDS ${PKG_DEPS}
)

set(SOURCES
  math/integral.cc
  math/sin_table.cc
  math/angle.cc
  math/integral.cc
  # geometry
  math/aabox2d.cc
  math/box2d.cc
  math/line_segment2d.cc
  math/math_utils.cc
  math/polygon2d.cc
  math/vec2d.cc
  # cartesian
  math/cartesian_frenet_conversion.cc
  util/string_util.cc
  )

add_library(common SHARED
  ${SOURCES}
  ${PROTO_HDRS}
  ${PROTO_SRCS})
#target_include_directories(common PUBLIC
#  ${CMAKE_CURRENT_SOURCE_DIR}
#  ${PROTOBUF_INCLUDE_DIRS}
#  )

#target_compile_options(common PUBLIC -I /usr/local/include -pthread -L /usr/local/lib)
target_link_libraries(common
  ${catkin_LIBRARIES}
  ${PROTOBUF_LIBRARIES}
  )

#[[if (CATKIN_ENABLE_TESTING)
  catkin_add_gtest(common_tests
    common_tests.cpp
    math/vec2d_test.cc)

  target_link_libraries(common_tests
    ${catkin_LIBRARIES}
    common)
endif (CATKIN_ENABLE_TESTING)
]]

#############
## Install ##
#############
set(DIRS math util time vehicle_state data configs adapters status transform_listener monitor_log kv_db filters)

# install all the headers to the install space, mirror the structure
install(DIRECTORY ${DIRS}
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".svn" EXCLUDE
)

# install all the headers to devel space since we export ${CATKIN_DEVEL_PREFIX}/include/
# to catkin package instead of the include folder in the root
install(DIRECTORY ${DIRS}
        DESTINATION ${CATKIN_DEVEL_PREFIX}/include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".svn" EXCLUDE
)
