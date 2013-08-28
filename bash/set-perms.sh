#!/bin/bash
# file: /usr/local/sbin/cmassoc/set-perms.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
#
# --------------------------------------------------------------------

if [ 1 ]; then

echo "setting binary and library folder and file permissions ..."
for file in /{{bin,sbin,lib},usr/{bin,sbin,lib,local/{bin,sbin,lib},cyrus/{bin,sbin,lib},gnome/{bin,sbin,lib}}}/*; do
	  if [ -d ${file} ]; then
#		echo "... ${file}"
		chown root:root ${file}
		chmod 0755 ${file}  
	elif [ -L ${file} ]; then
		chown root:root ${file}
		chmod 0555 ${file}  
	elif [ -x ${file} ]; then
		chown root:root ${file}
		chmod 0555 ${file}  
	else
		chown root:root ${file}
		chmod 0444 ${file}  
	fi
done

fi

# ====================================================================
#
# --------------------------------------------------------------------

if [ 1 ]; then

echo "setting configuration folder and file permissions ..."
for file in /etc/*; do
	  if [ -d ${file} ]; then
#		echo "... ${file}"
		chown root:root ${file}
		chmod 2755 ${file}
	elif [ -f ${file} ]; then
		chown root:root ${file}
		chmod 0444 ${file}  
	fi
done

echo "setting configuration folder permissions for mail ..."
for file in /etc/{mail,exim,cyrus}; do
#	echo "... ${file}"
	chown root:mail ${file} 
done

echo "setting primary password file permissions ..."
for file in /etc/{passwd,group}; do
#	echo "... ${file}"
	chown root:root ${file}
        chmod 0644 ${file}
done  

echo "setting secondary password file permissions ..."
for file in /etc/{shadow,gshadow,passwd-,group-,shadow-,gshadow-}; do
#	echo "... ${file}"
	chown root:root ${file}
        chmod 0640 ${file}
done  

echo "setting pam module permissions ..."
chown root:root /etc/pam.d/*
chmod 0444 /etc/pam.d/*

fi

# ====================================================================
#
# --------------------------------------------------------------------

if [ ]; then

echo "setting /var file permissions ..."
for file in /var/{lock,log,run,tmp}; do
	chown root:root ${file}
	chmod 1777 ${file}
done

for file in /var/{cache,opt,mail,spool,state}; do
	chown root:root ${file}
	chmod 2755 ${file}
done

for file in /var/{backups,cache/bind}; do
	chmod 0755 ${file};
done

fi

touch /var/log/btmp
chown root:utmp /var/log/btmp
chmod 620 /var/log/btmp

# ====================================================================
# set init script ownerships and permissions;
# --------------------------------------------------------------------

. set-init-perms.sh

# ====================================================================
# set runjobs script ownerships and permissions;
# --------------------------------------------------------------------

. set-runjobs-perms.sh

# ====================================================================
# home and mail specific permissions;
# --------------------------------------------------------------------

. set-home-perms.sh
. set-mail-perms.sh

# ====================================================================
# check init files for missing links; 
# --------------------------------------------------------------------

. check-init-links.sh

# ====================================================================
# finish; 
# --------------------------------------------------------------------

exit 0  

