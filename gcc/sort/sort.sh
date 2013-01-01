#!/bin/bash
# file: sort/sort.sh

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c adheap.c
gcc -Wall -Wextra -Wno-unused-parameter -c deheap.c
gcc -Wall -Wextra -Wno-unused-parameter -c enheap.c
gcc -Wall -Wextra -Wno-unused-parameter -c hsort.c
gcc -Wall -Wextra -Wno-unused-parameter -c isort.c
gcc -Wall -Wextra -Wno-unused-parameter -c psort.c
gcc -Wall -Wextra -Wno-unused-parameter -c qsort.c
gcc -Wall -Wextra -Wno-unused-parameter -c reheap.c
gcc -Wall -Wextra -Wno-unused-parameter -c sift.c
gcc -Wall -Wextra -Wno-unused-parameter -c sort.c
gcc -Wall -Wextra -Wno-unused-parameter -c ssort.c
gcc -Wall -Wextra -Wno-unused-parameter -c swap.c
gcc -Wall -Wextra -Wno-unused-parameter -c vfinal.c
gcc -Wall -Wextra -Wno-unused-parameter -c vfirst.c
gcc -Wall -Wextra -Wno-unused-parameter -c vindex.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.o

