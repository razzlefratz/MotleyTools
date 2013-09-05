#!/bin/bash

# ====================================================================
#
# --------------------------------------------------------------------

GROUP=fae
PASSWORD=abN/qM.L/H8EQ 
COMPUTER=appslinux01
USERROOT=/home

# ====================================================================
#
# --------------------------------------------------------------------

if [ -z ${1} ]; then
	echo "No user given."
	exit 1
elif [ -z ${2} ]; then
	echo "No forename given."
	exit 1
elif [ -z ${3} ]; then
	echo "No surname given."
	exit 1
elif [ ! -d ${USERROOT} ]; then
	echo "Folder ${USERROOT} does not exist."
	exit 1
elif [ ${HOSTNAME} != ${COMPUTER} ]; then
	echo "Server is not ${COMPUTER}'."
	exit 1
fi

# ====================================================================
# add user to password file;
# --------------------------------------------------------------------

useradd -g ${GROUP} ${1}
usermod -d ${USERROOT}/${1} ${1}
usermod -s /bin/bash ${1}
usermod -p ${PASSWORD} ${1}

# ====================================================================
# create smb.conf entry;
# --------------------------------------------------------------------

smbpasswd -a ${1}
cat >> /etc/samba/smb.conf << EOF
[${1}]
	comment = "${2} ${3}"
	path = /home/${1}
	force user = ${1}
#	browseable = no

EOF

# ====================================================================
# create user folder;
# --------------------------------------------------------------------

if [ ! -d ${USERROOT}/${1} ]; then
	install -m 6775 -o ${1} -g ${GROUP} -d ${USERROOT}/${1}
fi


