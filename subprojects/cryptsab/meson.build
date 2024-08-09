project('cryptsab', 'c')

libcrypt = shared_library('cryptsab', ['crypt.c', 'compress.c'], dependencies: [dependency('openssl'), dependency('libarchive')])

cryptsab_dep = declare_dependency(link_with: libcrypt)