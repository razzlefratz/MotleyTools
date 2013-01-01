# =
# libgen source files;
# -
_basename.c: _basename.c files.h _libgen.h
_dirname.c: _dirname.c files.h _libgen.h sizes.h
libgen.c: libgen.c _basename.c _dirname.c
