#!/bin/bash
# file: /usr/local/bin/cmassoc/archive.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
#
# --------------------------------------------------------------------

backup=/disk2/backup
hostnames="ariel atlas aries zeus"

# ====================================================================
#
# --------------------------------------------------------------------

cd ${backup}
for hostname in ${hostnames}; do
	if [ ${hostname} != ${HOSTNAME} ]; then
		scp root@${hostname}:${backup}/* ${backup}
	fi
done

# ====================================================================
#
# --------------------------------------------------------------------

echo done.

