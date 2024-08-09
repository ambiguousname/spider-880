cryptsab = subproject('cryptsab')
cryptsab_dep = cryptsab.get_variable('cryptsab_dep')

# Modify python script to just instead write to here?
navsab = static_library('navsab', ['page.cpp', 'tags.cpp'], build_by_default: true)

page_list = run_command('grab_pages.sh', check: true)
pages = page_list.stdout().strip().split('\n')

python = find_program('python')

pages = custom_target(
	'pages', 
	output: 'pages.tar.z.enc',
	input: pages,
	command: [python, 'pagesbuild.py', cryptsab.get_variable('libcrypt').full_path(), '@OUTPUT@']
)