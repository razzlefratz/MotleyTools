#!/bin/bash
# file: stdio/stdio.sh

# ====================================================================
#
# --------------------------------------------------------------------

echo skipping ...
exit

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c _bufopen.c
gcc -Wall -Wextra -Wno-unused-parameter -c _dopen.c
gcc -Wall -Wextra -Wno-unused-parameter -c _fclose.c
gcc -Wall -Wextra -Wno-unused-parameter -c _fcopy.c
gcc -Wall -Wextra -Wno-unused-parameter -c _fdcopy.c
gcc -Wall -Wextra -Wno-unused-parameter -c _fdopen.c
gcc -Wall -Wextra -Wno-unused-parameter -c _ffill.c
gcc -Wall -Wextra -Wno-unused-parameter -c _fflush.c
gcc -Wall -Wextra -Wno-unused-parameter -c _fgetc.c
gcc -Wall -Wextra -Wno-unused-parameter -c _fgets.c
gcc -Wall -Wextra -Wno-unused-parameter -c _filbuf.c
gcc -Wall -Wextra -Wno-unused-parameter -c _fillbuf.c
gcc -Wall -Wextra -Wno-unused-parameter -c _flsbuf.c
gcc -Wall -Wextra -Wno-unused-parameter -c _flushbuf.c
gcc -Wall -Wextra -Wno-unused-parameter -c _fopen.c
gcc -Wall -Wextra -Wno-unused-parameter -c _fpinit.c
gcc -Wall -Wextra -Wno-unused-parameter -c _fputc.c
gcc -Wall -Wextra -Wno-unused-parameter -c _fputs.c
gcc -Wall -Wextra -Wno-unused-parameter -c _fread.c
gcc -Wall -Wextra -Wno-unused-parameter -c _freopen.c
gcc -Wall -Wextra -Wno-unused-parameter -c _fwrite.c
gcc -Wall -Wextra -Wno-unused-parameter -c _getc.c
gcc -Wall -Wextra -Wno-unused-parameter -c _getchar.c
gcc -Wall -Wextra -Wno-unused-parameter -c _gets.c
gcc -Wall -Wextra -Wno-unused-parameter -c _iob.c
gcc -Wall -Wextra -Wno-unused-parameter -c _program.c
gcc -Wall -Wextra -Wno-unused-parameter -c _putc.c
gcc -Wall -Wextra -Wno-unused-parameter -c _putchar.c
gcc -Wall -Wextra -Wno-unused-parameter -c _puts.c
gcc -Wall -Wextra -Wno-unused-parameter -c _setbuf.c
gcc -Wall -Wextra -Wno-unused-parameter -c _setvbuf.c
gcc -Wall -Wextra -Wno-unused-parameter -c _stdio.c
gcc -Wall -Wextra -Wno-unused-parameter -c _strerror.c
gcc -Wall -Wextra -Wno-unused-parameter -c _unget.c
gcc -Wall -Wextra -Wno-unused-parameter -c _ungetc.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.o

