subdir('spider_navigator')
subdir('util')
subdir('database')

cpp_comp = meson.get_compiler('cpp')

# TODO: Make this a custom install script? Instead of having to search for it.
# https://mesonbuild.com/Installing.html
fltk = cpp_comp.find_library('fltk', required: true)
fltk_images = cpp_comp.find_library('fltk_images', required: true)
fltk_gl = cpp_comp.find_library('fltk_gl', required: true)

opengl = dependency(['gl', 'opengl'], required: true)

glm = dependency('glm', required: true)
glew = dependency('glew', required: true)

sqlite3 = dependency('sqlite3', required: true)

math = meson.get_compiler('c').find_library('m')

src = ['main.cpp', 'win_screen.cpp']
dependencies = [fltk, fltk_images, fltk_gl, opengl, glew, glm, sqlite3, math]
link_args = []

windows = import('windows')
if target_machine.system() == 'windows'
	src += windows.compile_resources('./icon.rc', './main.rc')
endif

if target_machine.system() == 'linux'
	# Link statically so we can hopefully aim for something distro-agnostic.
	link_args += '-static-libstdc++'
endif


exe = executable('spider-880', src, link_args: link_args, dependencies: dependencies, link_with: [utillib, databaselib, navsab], install: true)

test('basic', exe)