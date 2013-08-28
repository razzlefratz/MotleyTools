#!/bin/bash
# file: /usr/local/bin/cmassoc/lockout.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# define variables;
# --------------------------------------------------------------------

IFS=':'
nowhere=/dev/null
noshell=/bin/false

# ====================================================================
# read /etc/passwd;
# --------------------------------------------------------------------

exec 9>&0 </etc/passwd
while read username password uid gid title place shell; do
        if [ ${uid} -gt "0" ] && [ ${uid} -lt "100" ]; then
                syslog -eb ${0} "locked ${username}"
                usermod -L ${username}
        elif [ ${place} == ${nowhere} ]; then
                syslog -eb ${0} "locked ${username}"
                usermod -L ${username}
        elif [ ${shell} == ${noshell} ]; then
                syslog -eb ${0} "locked ${username}"
                usermod -L ${username}
	fi
done
exec 0>&9 9>&-

# ====================================================================
# finish;
# --------------------------------------------------------------------

exit ${?}

