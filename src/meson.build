subdir('spider_navigator')
subdir('util')
subdir('database')

cpp_comp = meson.get_compiler('cpp')

# TODO: Make this a custom install script? Instead of having to search for it.
# https://mesonbuild.com/Installing.html
fltk = cpp_comp.find_library('fltk', required: true)
fltk_images = cpp_comp.find_library('fltk_images', required: true)
fltk_gl = cpp_comp.find_library('fltk_gl', required: true)

opengl = cpp_comp.find_library('opengl32', required: true)
glu = cpp_comp.find_library('glu32', required: true)

glm = dependency('glm', required: true)
glew = dependency('glew', required: true)

sqlite3 = dependency('sqlite3', required: true)

src = ['main.cpp', 'win_screen.cpp']
windows = import('windows')
if target_machine.system() == 'windows'
	src += windows.compile_resources('./icon.rc', './main.rc')
endif

exe = executable('spider-880', src, dependencies: [fltk, fltk_images, fltk_gl, opengl, glu, glew, glm, sqlite3], link_with: [utillib, navsab, databaselib], install: true)

test('basic', exe)