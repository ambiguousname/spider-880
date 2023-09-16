custom_target('filepages', build_always_stale: true, input: 'list.txt', output: 'pages.h', command: ['python', 'navigator.py'])

pageslib = static_library('pages', files.split('\n'))