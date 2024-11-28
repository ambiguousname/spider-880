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
fltk_gl = cpp_comp.find_library('fltk_gl', required: true)

opengl = cpp_comp.find_library('opengl32', required: true)
glu = cpp_comp.find_library('glu32', required: true)

glm = dependency('glm', required: true)
glew = dependency('glew', required: true)

sqlite3 = dependency('sqlite3', required: true)

libxml = dependency('libxml2', required: true)

src = ['main.cpp', 'win_screen.cpp']
windows = import('windows')
if target_machine.system() == 'windows'
	src += windows.compile_resources('./icon.rc', './main.rc')
endif

exe = executable('spider-880', src, link_args : links, dependencies: [fltk, fltk_images, fltk_gl, opengl, glu, glew, glm, sqlite3, libxml], link_with: [utillib, navsab, databaselib], install: true)

test('basic', exe)