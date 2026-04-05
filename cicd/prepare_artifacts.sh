#!/bin/sh

# Configuration
SCRIPT_DIR=$(cd $(dirname $0); pwd)
. "$SCRIPT_DIR/config.sh"

# Demo
mkdir -p ${ARTIFACTS_DIR}
cp ${DEOM_FILE} ${ARTIFACTS_DIR}

# Src
zip -r ${ARTIFACTS_DIR}/src.zip ${SRC_DIR}
