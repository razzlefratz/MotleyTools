#!/bin/bash
# file: libgen/libgen.sh

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c _basename.c
gcc -Wall -Wextra -Wno-unused-parameter -c _dirname.c
gcc -Wall -Wextra -Wno-unused-parameter -c libgen.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.o

