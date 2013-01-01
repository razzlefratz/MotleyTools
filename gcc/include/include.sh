#!/bin/bash
# file: include/include.sh

echo "skipping ..."
exit 

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c _filename.c
gcc -Wall -Wextra -Wno-unused-parameter -c _pathname.c
gcc -Wall -Wextra -Wno-unused-parameter -c broadcast.c
gcc -Wall -Wextra -Wno-unused-parameter -c checkpf.c
gcc -Wall -Wextra -Wno-unused-parameter -c datecomp.c
gcc -Wall -Wextra -Wno-unused-parameter -c daytime.c
gcc -Wall -Wextra -Wno-unused-parameter -c emalloc.c
gcc -Wall -Wextra -Wno-unused-parameter -c erealloc.c
gcc -Wall -Wextra -Wno-unused-parameter -c error.c
gcc -Wall -Wextra -Wno-unused-parameter -c error_at_line.c
gcc -Wall -Wextra -Wno-unused-parameter -c event.c
gcc -Wall -Wextra -Wno-unused-parameter -c getoptv.c
gcc -Wall -Wextra -Wno-unused-parameter -c getprocname.c
gcc -Wall -Wextra -Wno-unused-parameter -c getusername.c
gcc -Wall -Wextra -Wno-unused-parameter -c hostspec.c
gcc -Wall -Wextra -Wno-unused-parameter -c makefind.c
gcc -Wall -Wextra -Wno-unused-parameter -c makepath.c
gcc -Wall -Wextra -Wno-unused-parameter -c match.c
gcc -Wall -Wextra -Wno-unused-parameter -c mergepath.c
gcc -Wall -Wextra -Wno-unused-parameter -c midnight.c
gcc -Wall -Wextra -Wno-unused-parameter -c partfile.c
gcc -Wall -Wextra -Wno-unused-parameter -c partpath.c
gcc -Wall -Wextra -Wno-unused-parameter -c procname.c
gcc -Wall -Wextra -Wno-unused-parameter -c putoptv.c
gcc -Wall -Wextra -Wno-unused-parameter -c readpf.c
gcc -Wall -Wextra -Wno-unused-parameter -c removepf.c
gcc -Wall -Wextra -Wno-unused-parameter -c runscript.c
gcc -Wall -Wextra -Wno-unused-parameter -c setumask.c
gcc -Wall -Wextra -Wno-unused-parameter -c showfind.c
gcc -Wall -Wextra -Wno-unused-parameter -c signal_codes.c
gcc -Wall -Wextra -Wno-unused-parameter -c signal_names.c
gcc -Wall -Wextra -Wno-unused-parameter -c signals.c
gcc -Wall -Wextra -Wno-unused-parameter -c signalspec.c
gcc -Wall -Wextra -Wno-unused-parameter -c sockspec.c
gcc -Wall -Wextra -Wno-unused-parameter -c splitpath.c
gcc -Wall -Wextra -Wno-unused-parameter -c statement.c
gcc -Wall -Wextra -Wno-unused-parameter -c stov.c
gcc -Wall -Wextra -Wno-unused-parameter -c strargv.c
gcc -Wall -Wextra -Wno-unused-parameter -c strcut.c
gcc -Wall -Wextra -Wno-unused-parameter -c strfbits.c
gcc -Wall -Wextra -Wno-unused-parameter -c strfpid.c
gcc -Wall -Wextra -Wno-unused-parameter -c strlwr.c
gcc -Wall -Wextra -Wno-unused-parameter -c strsplit.c
gcc -Wall -Wextra -Wno-unused-parameter -c svfirst.c
gcc -Wall -Wextra -Wno-unused-parameter -c svindex.c
gcc -Wall -Wextra -Wno-unused-parameter -c svorder.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslog_error_at_line.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslog_event.c
gcc -Wall -Wextra -Wno-unused-parameter -c timespec.c
gcc -Wall -Wextra -Wno-unused-parameter -c trace.c
gcc -Wall -Wextra -Wno-unused-parameter -c uintspec.c
gcc -Wall -Wextra -Wno-unused-parameter -c userid.c
gcc -Wall -Wextra -Wno-unused-parameter -c username.c
gcc -Wall -Wextra -Wno-unused-parameter -c version.c
gcc -Wall -Wextra -Wno-unused-parameter -c waitspec.c
gcc -Wall -Wextra -Wno-unused-parameter -c weekdays.c
gcc -Wall -Wextra -Wno-unused-parameter -c writepf.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.o
