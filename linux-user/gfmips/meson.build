syscall_nr_generators += {
  'gfmips': generator(sh,
                    arguments: [ meson.current_source_dir() / 'syscallhdr.sh', '@INPUT@', '@OUTPUT@', '@EXTRA_ARGS@',
                                 '', '4000' ],
                    output: '@BASENAME@_nr.h')
}
