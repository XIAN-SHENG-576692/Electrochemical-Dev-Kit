#!/bin/sh

# Configuration
SCRIPT_DIR=$(cd $(dirname $0); pwd)
. "$SCRIPT_DIR/config.sh"

cmake --preset tests
cmake --build ${BUILD_DIR}
