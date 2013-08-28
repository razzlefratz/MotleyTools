#!/bin/bash
# file: /usr/local/sbin/cmassoc/set-mail-perms.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# environment strings;
# --------------------------------------------------------------------

IFS=':'

# ====================================================================
# create MAILROOM if missing;
# --------------------------------------------------------------------

MAILROOM=/var/mail
echo -n "mail folder [${MAILROOM}]: "; read
if [ ${REPLY} ]; then
	MAILROOM=${REPLY}
fi

if [ ! -d ${MAILROOM} ]; then
	echo "folder ${MAILROOM} does not exist or is not a folder."
	exit 1
fi

# ====================================================================
# set mail program file permissions; 
# --------------------------------------------------------------------

echo "setting mail file permissions ..."
if [ -x /usr/local/sbin/exim ]; then
	chown exim:mail ${MAILROOM}/{db,input,msglog}
fi

if [ -x /usr/local/bin/postfix ]; then
	chown root:postdrop /usr/local/bin/{postdrop,postqueue}
	for file in ${MAILROOM}/postfix/{active,bounce,corrupt,defer,deferred,flush,hold,incoming,pid,saved,trace};do
		chown root:root ${file}
		chmod 0700 ${file}
 	done
	for file in ${MAILROOM}/postfix/{maildrop,public}; do
		chown postfix:postdrop ${file}
	done
fi

# ====================================================================
# set mailbox file permissions; 
# --------------------------------------------------------------------

echo "setting mailbox file permissions ..."
chown root:root ${MAILROOM}
chmod 1775 ${MAILROOM}

exec 9>&0 </etc/passwd
while read username password uid gid homepath execpath; do
	mailbox=${MAILROOM}/${username}
	if [ -f ${mailbox} ]; then
		chown ${username}:mail ${mailbox}
		chmod 0600 ${mailbox}               
	fi
done
exec 0>&9 9>&-

# ====================================================================
#  
# --------------------------------------------------------------------

exit 0  

