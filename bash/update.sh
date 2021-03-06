#!/bin/bash
# file: /root/update.sh

# ====================================================================
# symbols;
# --------------------------------------------------------------------

. /etc/environment

# ====================================================================
# environment
# --------------------------------------------------------------------

if [ -z "${HOSTS}" ]; then
	echo "symbol HOSTS is undefined."
	exit 1
fi

# ====================================================================
# 
# --------------------------------------------------------------------

for host in ${HOSTS}; do
	echo "---> ${host}"
	scp /etc/environment /etc/hosts ${host}:/etc/
	scp /root/update.sh /root/ssh-keys.sh ${host}:/root/
done


