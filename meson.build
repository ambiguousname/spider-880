project('testing-fltk', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

flags = run_command('fltk-config', '--ldflags')

exe = executable('testing_fltk', 'testing_fltk.cpp',
  install : true, link_args : flags.stdout().strip().split(' '))

test('basic', exe)
