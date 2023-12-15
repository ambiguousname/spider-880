shaders = ['frag/base.glsl', 'vertex/base.glsl']

compilation = join_paths(meson.current_source_dir(), 'compile_shaders.sh')

run_target('shaders', command: ['sh', compilation, shaders, '-D', join_paths(meson.current_source_dir(), 'shaders'), '-O', join_paths(meson.build_root(), 'src/assets/shaders'), '-I', join_paths(meson.source_root(), 'm4-composites')])

asset_files = files('sis_logo.png', 'spider.png', 'victim.png', 'startup.wav', 'click.wav', 'error.wav', 'close.wav', 'check.wav', 'type.wav')

run_target('assets', command: ['cp', asset_files, join_paths(meson.build_root(), 'src/assets')])