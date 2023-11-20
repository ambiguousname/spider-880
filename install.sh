#!/bin/sh
# If you're looking for VS Code integration with Msys, see: https://code.visualstudio.com/docs/cpp/config-mingw
if [[ "$OSTYPE" == "darwin*" ]] && ! command -v bash > /dev/null; then
	echo "You "
	exit 1
fi

if ! command -v gcc > /dev/null; then
	if  command -v pacman > /dev/null ; then
		pacman -S mingw-w64-x86_64-toolchain
	fi
fi

if ! command -v pip > /dev/null; then
	if  command -v pacman > /dev/null ; then
		pacman -S mingw-w64-ucrt-x86_64-python mingw-w64-ucrt-x86_64-python-pip
	else
		sudo apt-get install python3 python3-pip python3-setuptools \
							python3-wheel
	fi
fi

if ! command -v meson > /dev/null; then
	if  command -v pacman > /dev/null ; then
		pacman -S mingw-w64-x86_64-meson
	elif command -v brew > /dev/null ; then
		brew install meson-python
		pip3 install meson
	else
		sudo apt-get install ninja-build
		pip3 install meson
	fi
fi

if  command -v pacman > /dev/null; then
	pacman -U https://mirror.msys2.org/mingw/ucrt64/mingw-w64-ucrt-x86_64-fltk-1.3.8-1-any.pkg.tar.zst
else
	sudo apt-get install libfltk1.3-dev libx11-dev
fi

if command -v pacman > /dev/null; then
	pacman -S mingw-w64-ucrt-x86_64-sqlite3
	pacman -S libsqlite-devel
elif command -v brew > /dev/null; then
	brew install sqlite
else
	sudo apt install sqlite3 libsqlite3-dev
fi

if command -v pacman > /dev/null; then
	pacman -S mingw-w64-ucrt-x86_64-glm
	pacman -S mingw-w64-ucrt-x86_64-glew
fi

# Meson build freaks out otherwise.
python3 ./src/spider_navigator/navigator.py

meson setup build