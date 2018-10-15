#!/usr/bin/env bash
set -e
CURRENT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd ${CURRENT_DIR} && cd ..
docker run -d -t --name xenial -v $(pwd):/home/port_apollo ubuntu
