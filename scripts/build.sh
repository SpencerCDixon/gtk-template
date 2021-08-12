#!/usr/bin/env bash
set -exuo pipefail

SCRIPTPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
cd "${SCRIPTPATH}/.."

rm -rf build
mkdir -p build
cd build

cmake .. -GNinja
ninja
