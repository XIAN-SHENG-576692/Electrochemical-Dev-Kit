#!/bin/sh

# Configuration
SCRIPT_DIR=$(cd $(dirname $0); pwd)
. "$SCRIPT_DIR/config.sh"

# demo
mkdir -p ${ARTIFACTS_DIR}
cp ${DEOM_FILE} ${ARTIFACTS_DIR}

# src
cd ${SRC_DIR} \
&& zip -r ${ARTIFACTS_DIR}/src.zip .
