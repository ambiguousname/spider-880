project('spider-880', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20']) 

# Avoids `UINT does not name a type.` on Windows for builds >=C++20.
if build_machine.system() == 'windows'
  add_global_arguments('-DWIN32', language : 'cpp')
endif

subdir('src')
subdir('assets')