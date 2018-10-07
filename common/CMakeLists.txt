cmake_minimum_required(VERSION 3.0)
project(common VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

set(PKG_DEPS
  glog_catkin
  cmake_modules_customized)

find_package(catkin REQUIRED COMPONENTS ${PKG_DEPS})
find_package(Protobuf REQUIRED)
# generate proto files for the library
protobuf_generate_cpp(PROTO_SRC PROTO_HEADER
  proto/pnc_point.proto
  proto/error_code.proto)

include_directories(
  include
  ${CMAKE_SOURCE_DIR}
  ${catkin_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${PROTOBUF_INCLUDE_DIRS}
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES common
  CATKIN_DEPENDS ${PKG_DEPS}
)

set(SOURCES
  math/integral.cc
  )

add_library(common SHARED
  ${SOURCES}
  ${PROTO_HEADER}
  ${PROTO_SRC})

target_link_libraries(common
  ${catkin_LIBRARIES}
  ${PROTOBUF_LIBRARY})


