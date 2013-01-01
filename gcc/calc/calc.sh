#!/bin/bash
# file: calc/calc.sh

# ====================================================================
# 
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c calc.c
gcc -Wall -Wextra -Wno-unused-parameter -c dpow.c
gcc -Wall -Wextra -Wno-unused-parameter -c dscale.c
gcc -Wall -Wextra -Wno-unused-parameter -c dtoa.c
gcc -Wall -Wextra -Wno-unused-parameter -c dtos.c
gcc -Wall -Wextra -Wno-unused-parameter -c gcd.c
gcc -Wall -Wextra -Wno-unused-parameter -c iabs.c
gcc -Wall -Wextra -Wno-unused-parameter -c ifact.c
gcc -Wall -Wextra -Wno-unused-parameter -c ipow.c
gcc -Wall -Wextra -Wno-unused-parameter -c iscale.c
gcc -Wall -Wextra -Wno-unused-parameter -c isgn.c
gcc -Wall -Wextra -Wno-unused-parameter -c lcm.c
gcc -Wall -Wextra -Wno-unused-parameter -c lcrng.c
gcc -Wall -Wextra -Wno-unused-parameter -c logn.c
gcc -Wall -Wextra -Wno-unused-parameter -c nblock.c
gcc -Wall -Wextra -Wno-unused-parameter -c pfact.c
gcc -Wall -Wextra -Wno-unused-parameter -c pmod.c
gcc -Wall -Wextra -Wno-unused-parameter -c qmod.c
gcc -Wall -Wextra -Wno-unused-parameter -c range.c
gcc -Wall -Wextra -Wno-unused-parameter -c smooth.c

# ====================================================================
# 
# --------------------------------------------------------------------

rm -f *.o

