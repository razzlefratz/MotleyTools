#!/bin/bash
# file: string/string.sh

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c _ctype.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strcasecmp.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strcat.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strchr.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strcmp.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strcpy.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strcspn.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strdup.c
gcc -Wall -Wextra -Wno-unused-parameter -c _string.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strlen.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strncat.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strncmp.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strncpy.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strpbrk.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strrchr.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strrev.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strspn.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strstr.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strtok.c
gcc -Wall -Wextra -Wno-unused-parameter -c _toascii.c
gcc -Wall -Wextra -Wno-unused-parameter -c _tocntrl.c
gcc -Wall -Wextra -Wno-unused-parameter -c _tolower.c
gcc -Wall -Wextra -Wno-unused-parameter -c _toprint.c
gcc -Wall -Wextra -Wno-unused-parameter -c _toupper.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.o

