#!/bin/bash
set -e  # exit on first error
CURRENT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
UBUNTU_CODENAME=$(lsb_release -sc)

main()
{
    install_dependencies
    install_protobuf
}

install_dependencies()
{
    sudo apt-get -y install autoconf automake libtool curl make g++ unzip
}


install_protobuf()
{
    cd /tmp && rm -rf protobuf-cpp-3.3.0.tar.gz
    wget https://github.com/google/protobuf/releases/download/v3.3.0/protobuf-cpp-3.3.0.tar.gz
    tar xzf protobuf-cpp-3.3.0.tar.gz
    cd protobuf-3.3.0   
    ./configure --prefix=/usr/local
    make -j4
    sudo make install 
    sudo ldconfig
}


main
