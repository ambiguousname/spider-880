#!/bin/bash
/ucrt64/bin/meson compile -C build

[ $? -ne 0 ] && read -p "Press enter to continue..."

# TODO: Move into meson.build file?
cp /ucrt64/bin/libfltk.dll /ucrt64/bin/libfltk_images.dll --target=./build/src/ 

./build/src/spider-880.exe
[ $? -ne 0 ] && read -p "Press enter to exit..."