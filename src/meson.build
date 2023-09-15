subdir('util')
subdir('spider-navigator')
# fltk = dependency('fltk', version : '>=1.3.8')

flags = run_command('fltk-config', '--ldflags')

links = flags.stdout().strip().split(' ')
links += '-lfltk_images'

# TODO: Make this a custom install script? Instead of having to search for it.
# https://mesonbuild.com/Installing.html
fltk = meson.get_compiler('cpp').find_library('fltk', required: true)

# incdir = include_directories('util')

exe = executable('spider-880', 'main.cpp',
  install : true, link_args : links, dependencies: [fltk], link_with: utillib)

test('basic', exe)