

py = custom_target('pages', input: 'navigator.py', output: ['list.txt'], command: ['python', '@INPUT@'])

file_list = run_command('cat', 'list.txt')
files = file_list.stdout().strip()

pageslib = static_library('pages', files.split('\n'))