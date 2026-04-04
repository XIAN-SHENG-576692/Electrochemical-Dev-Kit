#!/bin/sh

# Configuration
SCRIPT_DIR=$(cd $(dirname $0); pwd)
. "$SCRIPT_DIR/config.sh"

cmake --preset demo
cmake --build ${BUILD_DIR}
