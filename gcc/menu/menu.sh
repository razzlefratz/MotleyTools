#!/bin/bash
# file: math/math.sh

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c menudefine.c
gcc -Wall -Wextra -Wno-unused-parameter -c menudump.c
gcc -Wall -Wextra -Wno-unused-parameter -c menulength.c
gcc -Wall -Wextra -Wno-unused-parameter -c menulist.c
gcc -Wall -Wextra -Wno-unused-parameter -c menuload.c
gcc -Wall -Wextra -Wno-unused-parameter -c menulookup.c
gcc -Wall -Wextra -Wno-unused-parameter -c menuprefix.c
gcc -Wall -Wextra -Wno-unused-parameter -c menushow.c
gcc -Wall -Wextra -Wno-unused-parameter -c menusize.c
gcc -Wall -Wextra -Wno-unused-parameter -c menusort.c
gcc -Wall -Wextra -Wno-unused-parameter -c menuvolume.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.o

