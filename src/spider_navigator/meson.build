cpp_files = run_command('cat', 'list.txt')
files = cpp_files.stdout().strip()

incdir = include_directories(['../', './pages'])

to_compile = ['page.cpp', 'tags.cpp', './pages/deadbeef/deadbeefgl.cpp']
to_compile += files.split('\n')

# Modify python script to just instead write to here?
pageslib = static_library('pages', to_compile, build_by_default: true, include_directories: incdir)