#!/usr/bin/env bash
set -exuo pipefail

SCRIPT_PATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
cd "${SCRIPT_PATH}/.."

sudo apt install -y build-essential \
  ninja-build \
  cmake \
  libgtk-3-dev \
  libgtkmm-3.0-dev \
  libgtkmm-3.0-doc \
  devhelp
