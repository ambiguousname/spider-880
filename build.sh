#!/bin/bash
/ucrt64/bin/meson compile -C build

[ $? -ne 0 ] && read -p "Press enter to continue..."

./build/spider-880.exe
[ $? -ne 0 ] && read -p "Press enter to exit..."