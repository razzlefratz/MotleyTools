#!/bin/bash
# file: linux/linux/sh

echo skipping ...
exit

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c broadcast.c
gcc -Wall -Wextra -Wno-unused-parameter -c checkpf.c
gcc -Wall -Wextra -Wno-unused-parameter -c com.c
gcc -Wall -Wextra -Wno-unused-parameter -c ftype.c
gcc -Wall -Wextra -Wno-unused-parameter -c getgroupname.c
gcc -Wall -Wextra -Wno-unused-parameter -c getprocname.c
gcc -Wall -Wextra -Wno-unused-parameter -c getsocketname.c
gcc -Wall -Wextra -Wno-unused-parameter -c getusername.c
gcc -Wall -Wextra -Wno-unused-parameter -c getviewport.c
gcc -Wall -Wextra -Wno-unused-parameter -c groupname.c
gcc -Wall -Wextra -Wno-unused-parameter -c hostname.c
gcc -Wall -Wextra -Wno-unused-parameter -c isscript.c
gcc -Wall -Wextra -Wno-unused-parameter -c linux.c
gcc -Wall -Wextra -Wno-unused-parameter -c lsb-filename.c
gcc -Wall -Wextra -Wno-unused-parameter -c miniterm.c
gcc -Wall -Wextra -Wno-unused-parameter -c printk.c
gcc -Wall -Wextra -Wno-unused-parameter -c procname.c
gcc -Wall -Wextra -Wno-unused-parameter -c readpf.c
gcc -Wall -Wextra -Wno-unused-parameter -c removepf.c
gcc -Wall -Wextra -Wno-unused-parameter -c runscript.c
gcc -Wall -Wextra -Wno-unused-parameter -c set-fileflag.c
gcc -Wall -Wextra -Wno-unused-parameter -c setumask.c
gcc -Wall -Wextra -Wno-unused-parameter -c signal_codes.c
gcc -Wall -Wextra -Wno-unused-parameter -c signal_names.c
gcc -Wall -Wextra -Wno-unused-parameter -c signals.c
gcc -Wall -Wextra -Wno-unused-parameter -c signalspec.c
gcc -Wall -Wextra -Wno-unused-parameter -c sockaddrout.c
gcc -Wall -Wextra -Wno-unused-parameter -c spawn.c
gcc -Wall -Wextra -Wno-unused-parameter -c statement.c
gcc -Wall -Wextra -Wno-unused-parameter -c strfaddr.c
gcc -Wall -Wextra -Wno-unused-parameter -c strfpid.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_signals.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslog_basic.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslog_error.c
gcc -Wall -Wextra -Wno-unused-parameter -c syslog_error_at_line.c
gcc -Wall -Wextra -Wno-unused-parameter -c userid.c
gcc -Wall -Wextra -Wno-unused-parameter -c username.c
gcc -Wall -Wextra -Wno-unused-parameter -c writepf.c

# ====================================================================
#
# --------------------------------------------------------------------

fm -f *.o

