# port_apollo [![Build Status](https://travis-ci.com/yuzhangbit/port_apollo.svg?branch=master)](https://travis-ci.com/yuzhangbit/port_apollo)

* OS: ubuntu 16.04 LTS
* ROS: Kinetic

## Dependencies
* ros-kinetic-desktop
* protobuf >= 3.3.0 (according to [the docker installing script](https://github.com/ApolloAuto/apollo/blob/master/docker/build/installers/install_protobuf.sh))  
The default installation won't install some headers that the Apollo needs. Please use the [scripts/installer/install_protobuf.sh](https://github.com/yuzhangbit/port_apollo/blob/master/scripts/installer/install_protobuf.sh).
* [catkin_simple](https://github.com/catkin/catkin_simple.git)
* [glog_catkin](https://github.com/ethz-asl/glog_catkin.git)
* [Sultan](https://sultan.readthedocs.io/en/latest/), `optional`, for changing the `include` directories of the sources codes if you want to convert an apollo module to a normal ROS package by yourself.

## Compile and Test
```bash
git clone --recursive https://github.com/yuzhangbit/port_apollo.git
cd port_apollo
./scripts/installer/install_dependencies.sh # install all the dependencies
./scripts/build_pkg.sh  # build the apollo packages and run tests from apollo modules
```
