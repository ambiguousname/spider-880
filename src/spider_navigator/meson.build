
output = run_command('python', 'listfiles.py')

file_list = run_command('cat', 'list.txt')
files = file_list.stdout().strip()

dirs = output.stdout().strip().split('DIR:')
foreach in_files : dirs
	if in_files != ''
		message(in_files.strip())
		pages = custom_target('filepages', input: in_files.strip().split('\n'), output: 'pages.h', command: ['python', 'navigator.py', '@INPUT@'])
	endif
endforeach

pageslib = static_library('pages', files.split('\n'))