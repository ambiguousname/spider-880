cryptsab = subproject('cryptsab', required: true)
cryptsab_dep = cryptsab.get_variable('cryptsab_dep')

libxmlpp = dependency('libxml++-3.0', required: true)

incdir = include_directories('../')

navsab = static_library('navsab', ['browser.cpp', 'tags.cpp'], dependencies: [cryptsab_dep, libxmlpp], include_directories: incdir)

python = find_program('python')

custom_target(
	'pages', 
	output: 'pages.tar.z.enc',
	input: 'pagesbuild.py',
	build_always_stale: true,
	build_by_default: true,
	depends: [cryptsab.get_variable('libcryptsab')],
	command: [python, '@INPUT@', cryptsab.get_variable('libcryptsab').full_path(), '@OUTPUT@'],
	install: true,
	install_dir: 'bin/spider_navigator'
)