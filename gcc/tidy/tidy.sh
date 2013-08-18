#!/bin/bash
# file: tidy/tidy.sh

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c advance.c
gcc -Wall -Wextra -Wno-unused-parameter -c collect.c
gcc -Wall -Wextra -Wno-unused-parameter -c comment.c
gcc -Wall -Wextra -Wno-unused-parameter -c content-css.c
gcc -Wall -Wextra -Wno-unused-parameter -c content.c
gcc -Wall -Wextra -Wno-unused-parameter -c context-css.c
gcc -Wall -Wextra -Wno-unused-parameter -c context.c
gcc -Wall -Wextra -Wno-unused-parameter -c discard.c
gcc -Wall -Wextra -Wno-unused-parameter -c divider.c
gcc -Wall -Wextra -Wno-unused-parameter -c endline.c
gcc -Wall -Wextra -Wno-unused-parameter -c escaped.c
gcc -Wall -Wextra -Wno-unused-parameter -c fortran.c
gcc -Wall -Wextra -Wno-unused-parameter -c literal.c
gcc -Wall -Wextra -Wno-unused-parameter -c mention.c
gcc -Wall -Wextra -Wno-unused-parameter -c nmtoken.c
gcc -Wall -Wextra -Wno-unused-parameter -c newline.c
gcc -Wall -Wextra -Wno-unused-parameter -c nocomment.c
gcc -Wall -Wextra -Wno-unused-parameter -c nocontext.c
gcc -Wall -Wextra -Wno-unused-parameter -c noliteral.c
gcc -Wall -Wextra -Wno-unused-parameter -c consume.c
gcc -Wall -Wextra -Wno-unused-parameter -c connect.c
gcc -Wall -Wextra -Wno-unused-parameter -c keep.c
gcc -Wall -Wextra -Wno-unused-parameter -c find.c
gcc -Wall -Wextra -Wno-unused-parameter -c tidy.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -r *.o

