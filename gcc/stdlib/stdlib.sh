#!/bin/bash
# file: stdlib/stdlib.sh

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c _alloc.c
gcc -Wall -Wextra -Wno-unused-parameter -c _atof.c
gcc -Wall -Wextra -Wno-unused-parameter -c _atoi.c
gcc -Wall -Wextra -Wno-unused-parameter -c _atol.c
gcc -Wall -Wextra -Wno-unused-parameter -c _bindex.c
gcc -Wall -Wextra -Wno-unused-parameter -c _bsearch.c
gcc -Wall -Wextra -Wno-unused-parameter -c _calloc.c
gcc -Wall -Wextra -Wno-unused-parameter -c _cfree.c
gcc -Wall -Wextra -Wno-unused-parameter -c _exit.c
gcc -Wall -Wextra -Wno-unused-parameter -c _free.c
gcc -Wall -Wextra -Wno-unused-parameter -c _itoa.c
gcc -Wall -Wextra -Wno-unused-parameter -c _malloc.c
gcc -Wall -Wextra -Wno-unused-parameter -c _memchr.c
gcc -Wall -Wextra -Wno-unused-parameter -c _memcmp.c
gcc -Wall -Wextra -Wno-unused-parameter -c _memcpy.c
gcc -Wall -Wextra -Wno-unused-parameter -c _memmove.c
gcc -Wall -Wextra -Wno-unused-parameter -c _memory.c
gcc -Wall -Wextra -Wno-unused-parameter -c _memset.c
gcc -Wall -Wextra -Wno-unused-parameter -c _qsort.c
gcc -Wall -Wextra -Wno-unused-parameter -c _srand.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.o

