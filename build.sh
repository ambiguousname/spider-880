#!/bin/bash
/ucrt64/bin/meson compile -C build

./build/spider-880.exe
[ $? -ne 0 ] && read -p "Press enter to exit..."