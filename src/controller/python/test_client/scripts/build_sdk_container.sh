#! /usr/bin/env bash

# Skip creating environment if it already exists
if [[ -z "${CHIP_SDK_ROOT}" ]]; then
  source ./scripts/activate_environment.sh
fi

# Build CHIP SDK
$TEST_CLIENT_ROOT/scripts/build_sdk.sh

# Build Docker image
$TEST_CLIENT_ROOT/scripts/build_container.sh
