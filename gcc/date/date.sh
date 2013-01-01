#!/bin/bash
# file: date/date.sh

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c annum.c
gcc -Wall -Wextra -Wno-unused-parameter -c arctime.c
gcc -Wall -Wextra -Wno-unused-parameter -c date.c
gcc -Wall -Wextra -Wno-unused-parameter -c datecomp.c
gcc -Wall -Wextra -Wno-unused-parameter -c datespec.c
gcc -Wall -Wextra -Wno-unused-parameter -c dayofwk.c
gcc -Wall -Wextra -Wno-unused-parameter -c dayofyr.c
gcc -Wall -Wextra -Wno-unused-parameter -c daytime.c
gcc -Wall -Wextra -Wno-unused-parameter -c encodetime.c
gcc -Wall -Wextra -Wno-unused-parameter -c endofmo.c
gcc -Wall -Wextra -Wno-unused-parameter -c fridate.c
gcc -Wall -Wextra -Wno-unused-parameter -c isleap.c
gcc -Wall -Wextra -Wno-unused-parameter -c logtime.c
gcc -Wall -Wextra -Wno-unused-parameter -c logtm.c
gcc -Wall -Wextra -Wno-unused-parameter -c midnight.c
gcc -Wall -Wextra -Wno-unused-parameter -c mondate.c
gcc -Wall -Wextra -Wno-unused-parameter -c month.c
gcc -Wall -Wextra -Wno-unused-parameter -c month2.c
gcc -Wall -Wextra -Wno-unused-parameter -c months.c
gcc -Wall -Wextra -Wno-unused-parameter -c delay.c
gcc -Wall -Wextra -Wno-unused-parameter -c startofperiod.c
gcc -Wall -Wextra -Wno-unused-parameter -c strtime.c
gcc -Wall -Wextra -Wno-unused-parameter -c strtm.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_date1.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_date2.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_month.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_wkday.c
gcc -Wall -Wextra -Wno-unused-parameter -c timecomp.c
gcc -Wall -Wextra -Wno-unused-parameter -c timespec.c
gcc -Wall -Wextra -Wno-unused-parameter -c waitspec.c
gcc -Wall -Wextra -Wno-unused-parameter -c weekdate.c
gcc -Wall -Wextra -Wno-unused-parameter -c weekdays.c
gcc -Wall -Wextra -Wno-unused-parameter -c workdate.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.o

