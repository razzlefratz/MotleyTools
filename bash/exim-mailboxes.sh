#!/bin/bash
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# environment strings;
# --------------------------------------------------------------------

MAILPATH=/var/mail
IFS=':'

# ====================================================================
# create MAILPATH if missing;
# --------------------------------------------------------------------

echo -n "mail folder [${MAILPATH}]: ": read
if [ ${REPLY} ]; then
	MAILPATH=${REPLY}
fi

if [ ! -d ${MAILPATH} ]; then
	echo "creating ${MAILPATH}"
	install -m 1770 -o root -g mail -d ${MAILPATH}
fi

if [ ! -d ${MAILPATH} ]; then
	echo "can't create ${MAILPATH}"
	exit 1
fi

# ====================================================================
# read /etc/passwd;
# --------------------------------------------------------------------

exec 9>&0 </etc/passwd
while read username password uid gid homepath execpath; do
	if [ ${uid} -eq "65534" ]; then
		continue
	fi
	if [ ${gid} -eq "65534" ]; then
		continue
	fi
        if [ ${gid} -ge "1000" ]; then
		echo -n "user ${username}"
		mailbox=${MAILPATH}/${username}
		if [ ! -f ${mailbox} ]; then
			echo -n "\t ... create ${mailbox}"
			touch ${mailbox}                  
		fi
		chown ${username}:mail ${mailbox}
		chmod 0600 ${mailbox}               
		echo
        fi
done
exec 0>&9 9>&-

# ====================================================================
# finish; 
# --------------------------------------------------------------------

echo done.

