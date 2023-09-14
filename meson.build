project('spider-880', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

flags = run_command('fltk-config', '--ldflags')
incdir = include_directories('/msys64/ucrt64/include/')

links = flags.stdout().strip().split(' ')
links += '-lfltk_images'
links += '-lpng'

exe = executable('spider-880', 'main.cpp',
  install : true, include_directories : incdir, link_args : links)

test('basic', exe)
