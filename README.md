# port_apollo

* OS: ubuntu 16.04 LTS
* ROS: Kinetic

## Dependencies

* protobuf >= 3.3.0 (according to [the docker installing script](https://github.com/ApolloAuto/apollo/blob/master/docker/build/installers/install_protobuf.sh))  
The default installation won't install some headers that the Apollo needs. Please use the [scripts/install_protobuf.sh](https://github.com/yuzhangbit/port_apollo/blob/feature_catkinize_planning/scripts/installer/install_protobuf.sh).
