
# Skip creating environment if it already exists
if [[ -z "${CHIP_SDK_ROOT}" ]]; then
  source ./scripts/activate_environment.sh
fi

gn gen $CHIP_SDK_ROOT/out/debug
ninja -C $CHIP_SDK_ROOT/out/debug
cp $CHIP_SDK_ROOT/out/debug/controller/python/*.whl $TEST_CLIENT_ROOT/