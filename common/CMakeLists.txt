cmake_minimum_required(VERSION 3.0)
project(common VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

set(CATKIN_ENABLE_TESTING ON)

# for the Protobuf
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")


find_package(Eigen3 QUIET)
if(NOT EIGEN3_FOUND)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(EIGEN3 REQUIRED eigen3)
  set(EIGEN3_INCLUDE_DIR ${EIGEN3_INCLUDE_DIRS})
endif()

set(PKG_DEPS
  glog_catkin
  roscpp
  tf2_msgs
  tf2_ros)
find_package(catkin REQUIRED COMPONENTS ${PKG_DEPS})
find_package(Protobuf REQUIRED)

set(PROTOS
  proto/header.proto
  proto/pnc_point.proto
  proto/error_code.proto
  proto/geometry.proto
  proto/drive_state.proto
  proto/vehicle_signal.proto
  configs/proto/vehicle_config.proto
  #vehicle_state/proto/vehicle_state.proto
  )

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${PROTOS})

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${PROTOBUF_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
)

catkin_package(
  ## export these folders to other catkin packages
  INCLUDE_DIRS ${CATKIN_DEVEL_PREFIX}/include
  LIBRARIES common
  CATKIN_DEPENDS ${PKG_DEPS}
)

set(CONFIGS_SRCS
  configs/config_gflags.cc
  configs/vehicle_config_helper.cc)

set(FILTER_SRCS
  filters/digital_filter.cc
  filters/digital_filter_coefficients.cc
  filters/mean_filter.cc)

set(MATH_SRCS
  math/sin_table.cc
  math/angle.cc
  math/path_matcher.cc
  math/search.cc
  math/linear_interpolation.cc
  math/integral.cc
  math/linear_quadratic_regulator.cc
  math/hermite_spline.h
  math/quaternion.h
  ## geometry
  math/aabox2d.cc
  math/box2d.cc
  math/line_segment2d.cc
  math/math_utils.cc
  math/math_utils.h
  math/polygon2d.cc
  math/vec2d.cc
  ## matrix
  math/matrix_operations.cc
  math/nonlinear_interpolation.cc
  ## frenet
  math/cartesian_frenet_conversion.cc
  ## filter
  math/kalman_filter.h
  math/extended_kalman_filter.h)

set(SOURCES
  transform_listener/transform_listener.cc
  ${MATH_SRCS}
  ${CONFIGS_SRCS}
  ${FILTER_SRCS}
  )

add_library(${PROJECT_NAME}
  ${SOURCES}
  ${PROTO_HDRS}
  ${PROTO_SRCS})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CATKIN_DEVEL_PREFIX}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}>
  )

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  ${PROTOBUF_LIBRARIES}
  )

if (CATKIN_ENABLE_TESTING)
  catkin_add_gtest(${PROJECT_NAME}_tests
    common_tests.cpp
    # filter tests
    filters/digital_filter_test.cc
    filters/digital_filter_coefficients_test.cc
    filters/mean_filter_test.cc
    # config
    configs/vehicle_config_helper_test.cc
    status/status_test.cc
    # math related tests
    math/vec2d_test.cc
    math/math_utils_test.cc
    math/integral_test.cc
    math/search_test.cc
    math/integral_test.cc
    math/vec2d_test.cc
    math/quaternion_test.cc
    math/euler_angles_zxy_test.cc
    math/aabox2d_test.cc
    math/angle_test.cc
    math/aaboxkdtree2d_test.cc
    math/box2d_test.cc
    math/polygon2d_test.cc
    math/line_segment2d_test.cc
    math/kalman_filter_test.cc
    math/cartesian_frenet_conversion_test.cc
    math/linear_interpolation_test.cc
    math/matrix_operations_test.cc)

  target_include_directories(${PROJECT_NAME}_tests
    PUBLIC
      $<BUILD_INTERFACE:${CATKIN_DEVEL_PREFIX}/include${PROJECT_NAME}>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
      $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}>
    )

  target_link_libraries(${PROJECT_NAME}_tests
    ${catkin_LIBRARIES}
    common)
endif (CATKIN_ENABLE_TESTING)


#############
## Install ##
#############
## don't miss any subfolders of the root, or you can't include the headers
## from other ros packages
set(DIRS proto math util time vehicle_state data configs adapters status transform_listener monitor_log kv_db filters)


# install all the headers to devel space since we export ${CATKIN_DEVEL_PREFIX}/include/
# to catkin package instead of the include folder in the root
install(DIRECTORY ${DIRS}
        DESTINATION ${CATKIN_DEVEL_PREFIX}/include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".svn" EXCLUDE
)
install(FILES log.h macro.h
        DESTINATION ${CATKIN_DEVEL_PREFIX}/include/${PROJECT_NAME}
)


# install all the headers to the install space, mirror the structure
# install the generated headers
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
        DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".svn" EXCLUDE
)

# install all the headers
install(DIRECTORY ${DIRS}
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".svn" EXCLUDE
)
# install header in the root
install(FILES log.h macro.h
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
