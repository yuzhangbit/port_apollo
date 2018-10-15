# port_apollo [![Build Status](https://travis-ci.com/yuzhangbit/port_apollo.svg?branch=master)](https://travis-ci.com/yuzhangbit/port_apollo)

* OS: ubuntu 16.04 LTS
* ROS: Kinetic

Please see [Using Apollo Algorithms in Your Normal ROS Package](https://yuzhangbit.github.io/tools/porting-apollo/) for details.

## Dependencies
* ros-kinetic-desktop
* protobuf >= 3.3.0 (according to [the docker installing script](https://github.com/ApolloAuto/apollo/blob/master/docker/build/installers/install_protobuf.sh))  
The default installation won't install some headers that the Apollo needs. Please use the [scripts/installer/install_protobuf.sh](https://github.com/yuzhangbit/port_apollo/blob/master/scripts/installer/install_protobuf.sh).
* [catkin_simple](https://github.com/catkin/catkin_simple.git)
* [glog_catkin](https://github.com/ethz-asl/glog_catkin.git)
* [Sultan](https://sultan.readthedocs.io/en/latest/), `optional`, for changing the `include` directories of the sources codes if you want to convert an apollo module to a normal ROS package by yourself.

## Repo Structure
```bash
port_apollo
├── LICENSE
├── README.md
├── scripts
│   ├── build_pkg.sh  # handy build script for ros workspace
│   ├── docker_build_image.sh # docker image for CI, you can use it locally as well
│   ├── docker_compile_pkgs.sh # repo-build script in docker container
│   ├── Dockerfile   # base docker file to build an image: ubuntu 16.04 + ros kinetic
│   ├── docker_install_dependencies.sh # install dependencies in the docker container
│   ├── docker_run.sh  # run the docker for the CI test
│   ├── installer  # dependencies install scripts go here
│   └── tools  # tools scripts
└── src
    ├── catkin_simple  # dependencies, ros package
    ├── glog_catkin  # dependencies, ros package
    ├── cmake  # cmake module folder to hold FindProtobuf.cmake
    ├── common  # apollo module, ros package
    ├── planning # apollo module, to be done
    ...
    └── other_module_name # apollo module, to be done
```

## Compile and Test
```bash
git clone --recursive https://github.com/yuzhangbit/port_apollo.git
cd port_apollo
./scripts/installer/install_dependencies.sh # install all the dependencies
./scripts/build_pkg.sh  # build the apollo packages and run tests from apollo modules
```
