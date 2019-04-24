cmake_minimum_required(VERSION 3.0)
project(planning VERSION 0.0.1 LANGUAGES CXX)

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
  common)
find_package(catkin REQUIRED COMPONENTS ${PKG_DEPS})
find_package(Protobuf REQUIRED)

set(PROTOS
    proto/spiral_curve_config.proto)

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${PROTOS})

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${PROTOBUF_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
)

catkin_package(
  ## export these folders to other catkin packages
  INCLUDE_DIRS
      ${CATKIN_DEVEL_PREFIX}/include
      ${CMAKE_CURRENT_SOURCE_DIR}
      ./
  LIBRARIES
  CATKIN_DEPENDS ${PKG_DEPS}
)

add_subdirectory(math)
#############
## Install ##
#############
## don't miss any subfolders of the root, or you can't include the headers
## from other ros packages
set(DIRS math)


# install all the headers to devel space since we export ${CATKIN_DEVEL_PREFIX}/include/
# to catkin package instead of the include folder in the root
install(DIRECTORY ./
        DESTINATION ${CATKIN_DEVEL_PREFIX}/include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".svn" EXCLUDE
)
