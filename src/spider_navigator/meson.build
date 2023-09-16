python = find_program('python')

cpp_files = run_command('cat', 'list.txt')
files = cpp_files.stdout().strip()

incdir = include_directories('../util/')

# Modify python script to just instead write to here?
pageslib = static_library('pages', files.split('\n'), build_by_default: true, include_directories: incdir)