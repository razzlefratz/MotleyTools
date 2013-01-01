#!/bin/bash
# file: link/link.sh

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c deque.c
gcc -Wall -Wextra -Wno-unused-parameter -c enque.c
gcc -Wall -Wextra -Wno-unused-parameter -c finditem.c
gcc -Wall -Wextra -Wno-unused-parameter -c freeitem.c
gcc -Wall -Wextra -Wno-unused-parameter -c link.c
gcc -Wall -Wextra -Wno-unused-parameter -c makeitem.c
gcc -Wall -Wextra -Wno-unused-parameter -c queue.c
gcc -Wall -Wextra -Wno-unused-parameter -c stackclear.c
gcc -Wall -Wextra -Wno-unused-parameter -c stackpop.c
gcc -Wall -Wextra -Wno-unused-parameter -c stackpush.c
gcc -Wall -Wextra -Wno-unused-parameter -c stacksize.c
gcc -Wall -Wextra -Wno-unused-parameter -c walklist.c
gcc -Wall -Wextra -Wno-unused-parameter -c walkloop.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.o

