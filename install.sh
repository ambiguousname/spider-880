#!/bin/sh
if ! command -v pip > /dev/null; then
	if  command -v pacman > /dev/null ; then
		pacman -S mingw-w64-ucrt-x86_64-python mingw-w64-ucrt-x86_64-python-pip
	else
		sudo apt-get install python3 python3-pip python3-setuptools \
							python3-wheel ninja-build
	fi
fi

if ! command -v meson > /dev/null; then
	pip3 install --user meson


	script_path=$(cygpath -u $USERPROFILE)/.local/bin
	echo "export PATH=\$PATH:$script_path" >> ~/.profile
	source ~/.profile
fi

if  command -v pacman > /dev/null ; then
	pacman -U https://mirror.msys2.org/mingw/ucrt64/mingw-w64-ucrt-x86_64-fltk-1.3.8-1-any.pkg.tar.zst
else
	sudo apt-get install libfltk1.3-dev libx11-dev
fi

meson setup build