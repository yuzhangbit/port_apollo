#!/usr/bin/env bash
set -e
CURRENT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
#install dependencies

docker exec -it xenial /bin/bash -c "source ros_entrypoint.sh && /home/port_apollo/scripts/build_pkg.sh"
