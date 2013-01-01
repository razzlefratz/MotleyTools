#!/bin/bash
# file: files/files.sh

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c cfopen.c
gcc -Wall -Wextra -Wno-unused-parameter -c fileexists.c
gcc -Wall -Wextra -Wno-unused-parameter -c fileinfolder.c
gcc -Wall -Wextra -Wno-unused-parameter -c fileinstring.c
gcc -Wall -Wextra -Wno-unused-parameter -c fileinvector.c
gcc -Wall -Wextra -Wno-unused-parameter -c filelist.c
gcc -Wall -Wextra -Wno-unused-parameter -c filepart.c
gcc -Wall -Wextra -Wno-unused-parameter -c files.c
gcc -Wall -Wextra -Wno-unused-parameter -c find.c
gcc -Wall -Wextra -Wno-unused-parameter -c findfile.c
gcc -Wall -Wextra -Wno-unused-parameter -c fopenparent.c
gcc -Wall -Wextra -Wno-unused-parameter -c fopensearch.c
gcc -Wall -Wextra -Wno-unused-parameter -c fullpath.c
gcc -Wall -Wextra -Wno-unused-parameter -c isdotdir.c
gcc -Wall -Wextra -Wno-unused-parameter -c makefind.c
gcc -Wall -Wextra -Wno-unused-parameter -c makepath.c
gcc -Wall -Wextra -Wno-unused-parameter -c match.c
gcc -Wall -Wextra -Wno-unused-parameter -c mergepath.c
gcc -Wall -Wextra -Wno-unused-parameter -c openpath.c
gcc -Wall -Wextra -Wno-unused-parameter -c openroot.c
gcc -Wall -Wextra -Wno-unused-parameter -c openauth.c
gcc -Wall -Wextra -Wno-unused-parameter -c partfile.c
gcc -Wall -Wextra -Wno-unused-parameter -c partpath.c
gcc -Wall -Wextra -Wno-unused-parameter -c path.c
gcc -Wall -Wextra -Wno-unused-parameter -c pathpart.c
gcc -Wall -Wextra -Wno-unused-parameter -c plain.c
gcc -Wall -Wextra -Wno-unused-parameter -c setfiletype.c
gcc -Wall -Wextra -Wno-unused-parameter -c showfind.c
gcc -Wall -Wextra -Wno-unused-parameter -c splitpath.c
gcc -Wall -Wextra -Wno-unused-parameter -c vfopen.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.o

