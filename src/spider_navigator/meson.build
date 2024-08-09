cryptsab = subproject('cryptsab')
cryptsab_dep = cryptsab.get_variable('cryptsab_dep')

incdir = include_directories('../')

# Modify python script to just instead write to here?
navsab = static_library('navsab', ['browser.cpp'], build_by_default: true, include_directories: incdir)

python = find_program('python')

pages = custom_target(
	'pages', 
	output: 'pages.tar.z.enc',
	input: 'pagesbuild.py',
	build_always: true,
	command: [python, '@INPUT@', cryptsab.get_variable('libcrypt').full_path(), '@OUTPUT@']
)