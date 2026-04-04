#!/bin/sh

# Configuration
SCRIPT_DIR=$(cd $(dirname $0); pwd)
. "$SCRIPT_DIR/config.sh"

ctest --test-dir ${BUILD_DIR}
