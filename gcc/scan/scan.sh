#!/bin/bash
# file: scan/scan.sh

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c copytoken.c
gcc -Wall -Wextra -Wno-unused-parameter -c copyquote.c
gcc -Wall -Wextra -Wno-unused-parameter -c havebreak.c
gcc -Wall -Wextra -Wno-unused-parameter -c haveclass.c
gcc -Wall -Wextra -Wno-unused-parameter -c havematch.c
gcc -Wall -Wextra -Wno-unused-parameter -c havetoken.c
gcc -Wall -Wextra -Wno-unused-parameter -c isbreak.c
gcc -Wall -Wextra -Wno-unused-parameter -c isclass.c
gcc -Wall -Wextra -Wno-unused-parameter -c ismatch.c
gcc -Wall -Wextra -Wno-unused-parameter -c isready.c
gcc -Wall -Wextra -Wno-unused-parameter -c istoken.c
gcc -Wall -Wextra -Wno-unused-parameter -c nextbreak.c
gcc -Wall -Wextra -Wno-unused-parameter -c nexttoken.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanalnum.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanalpha.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanblock.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanblockmatch.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanbreak.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanbreakmatch.c
gcc -Wall -Wextra -Wno-unused-parameter -c scancntrl.c
gcc -Wall -Wextra -Wno-unused-parameter -c scandigit.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanflush.c
gcc -Wall -Wextra -Wno-unused-parameter -c scangroup.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanident.c
gcc -Wall -Wextra -Wno-unused-parameter -c scaninput.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanlimit.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanprint.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanquote.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanquotematch.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanreset.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanspace.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanstart.c
gcc -Wall -Wextra -Wno-unused-parameter -c scantoken.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanuntil.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanuntilmatch.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanwhile.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanwhilematch.c
gcc -Wall -Wextra -Wno-unused-parameter -c scanwrite.c
gcc -Wall -Wextra -Wno-unused-parameter -c showtoken.c
gcc -Wall -Wextra -Wno-unused-parameter -c tokensize.c
gcc -Wall -Wextra -Wno-unused-parameter -c tokentext.c
gcc -Wall -Wextra -Wno-unused-parameter -c tokentype.c
gcc -Wall -Wextra -Wno-unused-parameter -c tovalue.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.o

