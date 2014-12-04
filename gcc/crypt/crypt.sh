#!/bin/bash
# file: crypt/crypt.sh

# ====================================================================
# 
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c SHA256.c
gcc -Wall -Wextra -Wno-unused-parameter -c SHA256Block.c
gcc -Wall -Wextra -Wno-unused-parameter -c SHA256Fetch.c
gcc -Wall -Wextra -Wno-unused-parameter -c SHA256Reset.c
gcc -Wall -Wextra -Wno-unused-parameter -c SHA256Write.c
gcc -Wall -Wextra -Wno-unused-parameter -c SHA256Print.c
gcc -Wall -Wextra -Wno-unused-parameter -c SHA256Ident.c
gcc -Wall -Wextra -Wno-unused-parameter -c SHA256Match.c
# gcc -Wall -Wextra -Wno-unused-parameter -c MD5.c
# gcc -Wall -Wextra -Wno-unused-parameter -c MD5Reset.c
# gcc -Wall -Wextra -Wno-unused-parameter -c MD5Write.c
# gcc -Wall -Wextra -Wno-unused-parameter -c MD5Block.c
# gcc -Wall -Wextra -Wno-unused-parameter -c MD5Fetch.c
# gcc -Wall -Wextra -Wno-unused-parameter -c MD5Print.c

# ====================================================================
# 
# --------------------------------------------------------------------

rm -f *.o

