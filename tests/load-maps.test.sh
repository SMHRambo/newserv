#!/bin/sh

set -e

EXECUTABLE="$1"
if [ -z "$EXECUTABLE" ]; then
  EXECUTABLE="./newserv"
fi

$EXECUTABLE --config=tests/config.json --system=system/ load-maps-test
