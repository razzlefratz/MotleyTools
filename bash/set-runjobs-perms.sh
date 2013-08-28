#!/bin/bash
# file: /usr/local/sbin/cmassoc/set-runjobs-perms.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# set runjobs script ownerships and permissions;
# --------------------------------------------------------------------

echo "setting runjob file permissions ..."
for file in /etc/runjobs.d/*; do
	if [ -d ${file} ]; then
		chown root:root ${file} -R
		chmod 0540 ${file} -R
		chmod 0750 ${file}
	else
		chown root:root ${file}
		chmod 0540 ${file}
	fi
done

# ====================================================================
#  
# --------------------------------------------------------------------

exit 0  

