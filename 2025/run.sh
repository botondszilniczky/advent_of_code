#!/bin/bash

set -e

if [ ! ${1} ]; then
    echo "Usage: ./run.sh <executable>"
    exit 1
fi

exe=${1}

shift
echo "Running ${exe} with arguments: $@"
./build/${exe} "$@"
