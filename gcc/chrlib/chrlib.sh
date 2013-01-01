#!/bin/bash
# file: chrlib/chrlib.sh

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c charset.c
gcc -Wall -Wextra -Wno-unused-parameter -c chrcount.c
gcc -Wall -Wextra -Wno-unused-parameter -c chrdef.c
gcc -Wall -Wextra -Wno-unused-parameter -c chresc.c
gcc -Wall -Wextra -Wno-unused-parameter -c chrescmap.c
gcc -Wall -Wextra -Wno-unused-parameter -c chrhex.c
gcc -Wall -Wextra -Wno-unused-parameter -c chrindex.c
gcc -Wall -Wextra -Wno-unused-parameter -c chrlib.c
gcc -Wall -Wextra -Wno-unused-parameter -c chrlwr.c
gcc -Wall -Wextra -Wno-unused-parameter -c chroct.c
gcc -Wall -Wextra -Wno-unused-parameter -c chrset.c
gcc -Wall -Wextra -Wno-unused-parameter -c chrsub.c
gcc -Wall -Wextra -Wno-unused-parameter -c chrtable.c
gcc -Wall -Wextra -Wno-unused-parameter -c chrtype.c
gcc -Wall -Wextra -Wno-unused-parameter -c chruesc.c
gcc -Wall -Wextra -Wno-unused-parameter -c chruescmap.c
gcc -Wall -Wextra -Wno-unused-parameter -c chrupr.c
gcc -Wall -Wextra -Wno-unused-parameter -c ct_ascii.c
gcc -Wall -Wextra -Wno-unused-parameter -c ct_ebcdic.c
gcc -Wall -Wextra -Wno-unused-parameter -c ct_fname.c
gcc -Wall -Wextra -Wno-unused-parameter -c ctoascii.c
gcc -Wall -Wextra -Wno-unused-parameter -c ctocntrl.c
gcc -Wall -Wextra -Wno-unused-parameter -c ctodigit.c
gcc -Wall -Wextra -Wno-unused-parameter -c ctolower.c
gcc -Wall -Wextra -Wno-unused-parameter -c ctoprint.c
gcc -Wall -Wextra -Wno-unused-parameter -c ctoupper.c
gcc -Wall -Wextra -Wno-unused-parameter -c cursor.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.o

