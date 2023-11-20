#!/bin/sh
# TODO: Move into meson.build file?
# As a run target.
python ./src/spider_navigator/navigator.py

# If this doesn't work, add C:/msys64/ucrt64/bin to your PATH
meson compile -C build

meson compile assets -C build

meson compile shaders -C build

status=$?
[ $status -ne 0 ] && read -p "meson compile: error $status Press enter to continue..."

# TODO: Move into meson.build file?
cp ./src/database/citizens.db --target=./build/src

cd ./build/src/
gdb spider-880.exe
status=$?
[ $status -ne 0 ] && read -p ".exe: error $status Press enter to exit..."