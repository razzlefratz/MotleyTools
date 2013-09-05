#!/bin/bash
# file: /usr/local/sbin/cmassoc/set-init-perms.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# set init script ownerships and permissions;
# --------------------------------------------------------------------

echo "setting init script permissions ..."
for file in /etc/init.d/*; do
	echo "... ${file}"
	chown root:root ${file}
        chmod 0540 ${file}
done

# ====================================================================
#  
# --------------------------------------------------------------------

exit 0  

