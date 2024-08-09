subdir(cryptsab)

# Modify python script to just instead write to here?
navsab = static_library('navsab', ['page.cpp', 'tags.cpp'], build_by_default: true, link_with: [cryptsab])

page_list = run_command('grab_pages.sh', check: true)

python = find_program('python')

message(navsab)

pages = custom_target('pages', 
	output: 'pages.tar.z.enc',
	input: page_list.stdout().strip().split('\n')
	command: [python, 'pagesbuild.py', navsab.full_path(), '@OUTPUT@']
	)