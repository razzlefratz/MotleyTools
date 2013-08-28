#!/bin/bash
# file: /usr/local/cmassoc/bin/update-init.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
#
# --------------------------------------------------------------------

for folder in /home/build/{linux,cmassoc-sysvinit-[0-9][.][0-9][.][0-9]}/etc/init.d; do
	echo ${folder}
	cp /etc/init.d/* ${folder}
done

# ====================================================================
#
# --------------------------------------------------------------------

exit 0

