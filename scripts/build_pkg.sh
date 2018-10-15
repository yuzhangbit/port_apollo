#!/usr/bin/env bash
set -e
CURRENT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

main(){
    cd ${CURRENT_DIR} && cd .. && REPO_DIR=$(pwd)
    cd ${REPO_DIR}
    catkin build
    catkin build --make-args tests
    ./devel/lib/common/common_tests
}

main
