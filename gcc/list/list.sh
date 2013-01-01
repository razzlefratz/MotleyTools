#!/bin/bash
# file: list/list.sh

# ====================================================================
# 
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c listappend.c
gcc -Wall -Wextra -Wno-unused-parameter -c listcolumn.c
gcc -Wall -Wextra -Wno-unused-parameter -c listcreate.c
gcc -Wall -Wextra -Wno-unused-parameter -c listdefine.c
gcc -Wall -Wextra -Wno-unused-parameter -c listdelete.c
gcc -Wall -Wextra -Wno-unused-parameter -c listdetect.c
gcc -Wall -Wextra -Wno-unused-parameter -c listexpand.c
gcc -Wall -Wextra -Wno-unused-parameter -c listinsert.c
gcc -Wall -Wextra -Wno-unused-parameter -c listload.c
gcc -Wall -Wextra -Wno-unused-parameter -c listremove.c
gcc -Wall -Wextra -Wno-unused-parameter -c listrubout.c
gcc -Wall -Wextra -Wno-unused-parameter -c listsort.c
gcc -Wall -Wextra -Wno-unused-parameter -c liststatus.c
gcc -Wall -Wextra -Wno-unused-parameter -c list.c

# ====================================================================
# 
# --------------------------------------------------------------------

rm -f *.o

