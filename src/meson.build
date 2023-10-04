subdir('spider_navigator')
subdir('util')
subdir('database')
# fltk = dependency('fltk', version : '>=1.3.8')

flags = run_command('fltk-config', '--ldflags')

links = flags.stdout().strip().split(' ')
links += '-lfltk_images'
links += '-lsqlite3'


incdir = include_directories('./spider_navigator/pages')

# TODO: Make this a custom install script? Instead of having to search for it.
# https://mesonbuild.com/Installing.html
fltk = meson.get_compiler('cpp').find_library('fltk', required: true)

# incdir = include_directories('util')

src = ['main.cpp']
windows = import('windows')
if build_machine.system() == 'windows'
	src += windows.compile_resources('./icon.rc')
endif

exe = executable('spider-880', src, link_args : links, include_directories:incdir, dependencies: [fltk], link_with: [utillib, pageslib, databaselib], cpp_args: '')

test('basic', exe)