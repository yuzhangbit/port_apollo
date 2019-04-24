
set(MATH_SRC
    spiral_curve/cubic_spiral_curve.cc
    spiral_curve/spiral_curve.cc
    spiral_curve/spiral_formula.cc
    spiral_curve/quintic_spiral_curve.cc)

add_library(spiral ${MATH_SRC})
target_link_libraries(spiral ${PROTOBUF_LIBRARIES})