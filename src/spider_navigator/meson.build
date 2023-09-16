python = find_program('python')

custom_target('htmltocppfiles', build_always_stale: true, build_by_default: true, input: 'navigator.py', output: 'list.txt', command: [python, '@INPUT@'])

cat = run_command('cat', 'list.txt')
files = cat.stdout().strip()

pageslib = static_library('pages', files.split('\n'))