#!/bin/bash
# file: math/math.sh

# ====================================================================
# 
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c _abs.c
gcc -Wall -Wextra -Wno-unused-parameter -c _atan.c
# gcc -Wall -Wextra -Wno-unused-parameter -c _ceil.c
gcc -Wall -Wextra -Wno-unused-parameter -c _cos.c
gcc -Wall -Wextra -Wno-unused-parameter -c _cosh.c
gcc -Wall -Wextra -Wno-unused-parameter -c _dabs.c
gcc -Wall -Wextra -Wno-unused-parameter -c _dmod.c
gcc -Wall -Wextra -Wno-unused-parameter -c _dpow.c
gcc -Wall -Wextra -Wno-unused-parameter -c _dsgn.c
gcc -Wall -Wextra -Wno-unused-parameter -c _e.c
gcc -Wall -Wextra -Wno-unused-parameter -c _exp.c
gcc -Wall -Wextra -Wno-unused-parameter -c _fabs.c
# gcc -Wall -Wextra -Wno-unused-parameter -c _floor.c
gcc -Wall -Wextra -Wno-unused-parameter -c _fmod.c
gcc -Wall -Wextra -Wno-unused-parameter -c _iabs.c
gcc -Wall -Wextra -Wno-unused-parameter -c _ipow.c
gcc -Wall -Wextra -Wno-unused-parameter -c _labs.c
gcc -Wall -Wextra -Wno-unused-parameter -c _log10.c
gcc -Wall -Wextra -Wno-unused-parameter -c _log.c
gcc -Wall -Wextra -Wno-unused-parameter -c _sgn.c
gcc -Wall -Wextra -Wno-unused-parameter -c _sin.c
gcc -Wall -Wextra -Wno-unused-parameter -c _sinh.c
gcc -Wall -Wextra -Wno-unused-parameter -c _sqrt.c
gcc -Wall -Wextra -Wno-unused-parameter -c _trig.c
gcc -Wall -Wextra -Wno-unused-parameter -c math.c

# ====================================================================
# 
# --------------------------------------------------------------------

rm -f *.o

