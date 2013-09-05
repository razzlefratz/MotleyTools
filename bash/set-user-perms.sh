#!/bin/bash
# file: /usr/local/sbin/cmassoc/set-user-perms.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# environment strings;
# --------------------------------------------------------------------

IFS=':'

# ====================================================================
# confirm HOMEROOM exists; 
# --------------------------------------------------------------------

HOMEROOM=/home/users
echo -n "home folder [${HOMEROOM}]: "; read
if [ ${REPLY} ]; then
	HOMEROOM=${REPLY}
fi

if [ ! -d ${HOMEROOM} ]; then
	echo "folder ${HOMEROOM} does not exist or is not a folder."
	exit 1
fi

# ====================================================================
# set folder permissions; 
# --------------------------------------------------------------------

echo "setting user folder permissions ..."
exec 9>&0 </etc/passwd
while read username password uid gid homepath execpath; do
	folder=${HOMEROOM}/${username}
	if [ -d ${folder} ]; then
       		if [ ${gid} -lt 100 ]; then
			echo remove ${folder}
			rm -fr ${folder}
			continue;
		fi
		echo ${folder}
		chown ${username}:root ${folder}
		chmod 1755 ${folder}               
	elif [ ${gid} -ge 1000 ]; then
		echo create ${folder}
		mkdir ${folder}  
		chown ${username}:root ${folder}
		chmod 1755 ${folder}               
	fi
done
exec 0>&9 9>&-

# ====================================================================
#  
# --------------------------------------------------------------------

exit 0  

