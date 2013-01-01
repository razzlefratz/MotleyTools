#!/bin/bash
# file: regex/regex.sh

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c regex.c
gcc -Wall -Wextra -Wno-unused-parameter -c regexcomp.c
gcc -Wall -Wextra -Wno-unused-parameter -c regexfree.c
gcc -Wall -Wextra -Wno-unused-parameter -c regexhelp.c
gcc -Wall -Wextra -Wno-unused-parameter -c regexmake.c
gcc -Wall -Wextra -Wno-unused-parameter -c regexmax.c
gcc -Wall -Wextra -Wno-unused-parameter -c regexmin.c
gcc -Wall -Wextra -Wno-unused-parameter -c regexscan.c
gcc -Wall -Wextra -Wno-unused-parameter -c regexshow.c
gcc -Wall -Wextra -Wno-unused-parameter -c regexspan.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.o

