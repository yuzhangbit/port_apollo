#!/usr/bin/env bash
set -e
CURRENT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd ${CURRENT_DIR}
docker build -t bit_xenial .
