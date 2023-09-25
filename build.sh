#!/bin/sh
python ./src/spider_navigator/navigator.py

/ucrt64/bin/meson compile -C build

status=$?
[ $status -ne 0 ] && read -p "meson compile: error $status Press enter to continue..."

# TODO: Move into meson.build file?
cp /ucrt64/bin/libfltk.dll /ucrt64/bin/libfltk_images.dll /ucrt64/bin/libpng16-16.dll --target=./build/src/ 

cp -r ./assets/ --target=./build/src

gdb ./build/src/spider-880.exe
status=$?
[ $status -ne 0 ] && read -p ".exe: error $status Press enter to exit..."