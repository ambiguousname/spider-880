project('cryptsab', 'c')

incdir = include_directories('include')

libcryptsab = shared_library('cryptsab', ['crypt.c', 'compress.c'], dependencies: [dependency('openssl'), dependency('libarchive')], include_directories: incdir)

cryptsab_dep = declare_dependency(include_directories: incdir, link_with: libcryptsab)