#!/bin/bash
# file: /usr/local/bin/cmassoc/check-runjobs.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
#
# --------------------------------------------------------------------

for file in /etc/runjobs.d/*; do
	echo ${file}
	if [ -d ${file} ]; then
		chown root:root ${file} -R
		chmod 0540 ${file} -R
		chmod 0750 ${file}
	else
		chown root:root ${file}
		chmod 0540 ${file}
	fi
done

