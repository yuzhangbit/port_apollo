#!/bin/bash
set -e  # exit on first error
CURRENT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
UBUNTU_CODENAME=$(lsb_release -sc)

main()
{
  install_sultan
  pwd
  .${CURRENT_DIR}/install_protobuf.sh
}

install_pkgs()
{
  sudo apt-get -y install ros-kinetic-tf2
}

install_sultan()
{
  echo "Installing sultan ........"
  sudo pip install --upgrade sultan
  echo "Sultan installed."
}


main
