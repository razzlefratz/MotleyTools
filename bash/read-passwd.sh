#!/bin/bash
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# define delimiter;
# --------------------------------------------------------------------

IFS=':'

# ====================================================================
# read /etc/passwd;
# --------------------------------------------------------------------

exec 9>&0 </etc/passwd
while read username password uid gid trash; do
	if [ -d /var/mail/${username} ] && [ gid == "1001" ]; then
		echo ${username};
	fi
done
exec 0>&9 9>&-
