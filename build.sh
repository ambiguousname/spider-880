#!/bin/sh
python3 ./src/spider_navigator/navigator.py

# If this doesn't work, add C:/msys64/ucrt64/bin to your PATH
meson compile -C build

status=$?
[ $status -ne 0 ] && read -p "meson compile: error $status Press enter to continue..."

# TODO: Move into meson.build file?
cp /ucrt64/bin/libfltk.dll /ucrt64/bin/libfltk_images.dll /ucrt64/bin/libpng16-16.dll ./build/src/ 

cp ./src/database/citizens.db ./build/src

cp -r ./assets/ ./build/src

cd ./build/src/

if command -v gdb > /dev/null; then
	gdb spider-880
else
	lldb spider-880
fi
status=$?
[ $status -ne 0 ] && read -p ".exe: error $status Press enter to exit..."