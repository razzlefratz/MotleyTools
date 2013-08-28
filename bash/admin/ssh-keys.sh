#!/bin/bash
# Published 2006 by Charles Maier Associates Limited for internal use;

# ====================================================================
# specify participating hosts by hostname; 
# --------------------------------------------------------------------

hosts="athene ariel atlas aries zeus"
hosts="appslinux01 appslinux02 dragon hotpants anchovy hokey pokey"
keyring=~/.ssh

# ====================================================================
# purge authorized_keys files;
# --------------------------------------------------------------------

rm -f authorized_keys
touch authorized_keys
chmod 0600 authorized_keys

# ====================================================================
# collect host rsa keys from participating hosts; compile authorized_keys file
# --------------------------------------------------------------------

for host in ${hosts}; do     
	echo "--->" ${host}
	scp -q ${host}:~/.ssh/id_rsa.pub ${host}_rsa.pub
	if [ -f ~/.ssh/${host}_rsa.pub ]; then
		cat ${host}_rsa.pub >> authorized_keys
		rm -f ${host}_rsa.pub
	fi
done

# ====================================================================
# distribute authorized_keys files to particpating hosts;
# --------------------------------------------------------------------

for host in ${hosts}; do     
	echo "<---" ${host} 
	scp -q authorized_keys ${host}:~/.ssh/authorized_keys
done

# ====================================================================
#
# --------------------------------------------------------------------

scp appslinux01:/root/.ssh/id_rsa.pub appslinux01_rsa.pub
scp appslinux02:/root/.ssh/id_rsa.pub appslinux02_rsa.pub
cat appslinux01_rsa.pub appslinux02_rsa.pub > backup_authorized_keys
rm -f appslinux01_rsa.pub appslinux02_rsa.pub 
scp backup_authorized_keys faedb@backup:.ssh/authorized_keys
rm -f backup_authorized_keys

