subdir('spider_navigator')
subdir('util')
subdir('database')
# fltk = dependency('fltk', version : '>=1.3.8')

flags = run_command('fltk-config', '--ldflags', '--use-gl')

links = flags.stdout().strip().split(' ')

cpp_comp = meson.get_compiler('cpp')

# TODO: Make this a custom install script? Instead of having to search for it.
# https://mesonbuild.com/Installing.html
fltk = cpp_comp.find_library('fltk', required: true)
fltk_images = cpp_comp.find_library('fltk_images', required: true)

sqlite3 = dependency('sqlite3', required: true)

glm = dependency('glm', required: true)
glew = dependency('glew', required: true)

libxmlpp = dependency('libxml++-3.0', required: true)

src = ['main.cpp', 'win_screen.cpp']
windows = import('windows')
if build_machine.system() == 'windows'
	src += windows.compile_resources('./icon.rc', './main.rc')
endif

exe = executable('spider-880', src, link_args : links, dependencies: [fltk, fltk_images, sqlite3, glew, glm, libxmlpp], link_with: [utillib, navsab, databaselib], install: true)

test('basic', exe)