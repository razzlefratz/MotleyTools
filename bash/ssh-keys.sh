#!/bin/bash
# Published 2006 by Charles Maier Associates Limited for internal use;

# ====================================================================
# specify participating hosts by hostname; 
# --------------------------------------------------------------------

. /etc/environment
if [ -z "${HOSTS}" ]; then
	echo "Symbol HOSTS is undefined"
	exit 1
fi

# ====================================================================
# create initial authorized_keys file;
# --------------------------------------------------------------------

cd ~/.ssh
if [ ! -f id_rsa.pub ]; then
	echo "File id_rsa.pub is missing or misplaced"
	exit 1;
fi
cp id_rsa.pub authorized_keys

# ====================================================================
# collect public rsa keys from participating hosts; 
# compile authorized_keys file
# --------------------------------------------------------------------

for host in ${HOSTS}; do     
	if [ ${host} != ${HOSTNAME} ]; then
		echo "--->" ${host}
		scp -q ${host}:~/.ssh/id_rsa.pub ${host}_rsa.pub
		if [ -f ~/.ssh/${host}_rsa.pub ]; then
			cat ${host}_rsa.pub >> authorized_keys
			rm -f ${host}_rsa.pub
		fi
	fi
done

# ====================================================================
# distribute authorized_keys files to particpating hosts;
# --------------------------------------------------------------------

for host in ${HOSTS}; do     
	echo "<---" ${host} 
	if [ ${host} != ${HOSTNAME} ]; then
		scp -q authorized_keys ${host}:~/.ssh/authorized_keys
	fi
done

# ====================================================================
# exit script;
# --------------------------------------------------------------------

exit 0

