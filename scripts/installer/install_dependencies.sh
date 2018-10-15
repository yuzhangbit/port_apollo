#!/usr/bin/env bash
set -e  # exit on first error
CURRENT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
UBUNTU_CODENAME=$(lsb_release -sc)

main()
{
  install_pkgs
  sudo pip install --upgrade pip
  sudo pip install -U catkin_tools
  install_sultan
  pwd && ls
  .${CURRENT_DIR}/install_protobuf.sh
}

install_pkgs()
{
  sudo apt-get -y install ros-kinetic-tf2 python-pip libgflags-dev
}

install_sultan()
{
  echo "Installing sultan ........"
  sudo pip install --upgrade sultan
  echo "Sultan installed."
}


main
