#!/bin/bash
# file: /usr/local/bin/cmassoc/userhomes.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# define and create HOMEPATH;
# --------------------------------------------------------------------

HOMEPATH=/home/users
IFS=':'

# ====================================================================
# define and create HOMEPATH;
# --------------------------------------------------------------------

echo -n "user folder [${HOMEPATH}]: "
read
if [ ${REPLY} ]; then
	HOMEPATH=${REPLY}
fi

if [ ! -d ${HOMEPATH} ]; then
	echo "creating ${HOMEPATH}"
	install -m 0755 -o root -g root -d ${HOMEPATH}
fi

if [ ! -d ${HOMEPATH} ]; then
	echo " ... can't create ${HOMEPATH}"
	exit 1
fi

# ====================================================================
# read /etc/passwd;
# --------------------------------------------------------------------

exec 9>&0 </etc/passwd
while read username password uid gid title folder shell; do
	if [ ${uid} -eq "65534" ]; then
		continue
	fi
        if [ ${gid} -ge "1000" ]; then
		echo -n "user ${username}"
		if [ ! -d ${folder} ]; then
			echo -n "\t ... create ${folder}"
			mkdir -p ${folder}
		fi
		chown ${uid}:${gid} ${folder}
		chmod 3755 ${folder}
		echo
        fi
done
exec 0>&9 9>&-

# ====================================================================
# finish;
# --------------------------------------------------------------------

echo done.

