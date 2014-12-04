#!/bin/bash
# file: clang/clang.sh

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c ccollect.c
gcc -Wall -Wextra -Wno-unused-parameter -c cfooter.c
gcc -Wall -Wextra -Wno-unused-parameter -c cheader.c
gcc -Wall -Wextra -Wno-unused-parameter -c cinclude.c
gcc -Wall -Wextra -Wno-unused-parameter -c clang.c
gcc -Wall -Wextra -Wno-unused-parameter -c coper.c
gcc -Wall -Wextra -Wno-unused-parameter -c cword.c
# gcc -Wall -Wextra -Wno-unused-parameter -c tl.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.o

