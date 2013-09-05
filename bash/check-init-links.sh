#!/bin/bash
# file: /usr/local/sbin/cmassoc/check-init-links.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# check rc[S0-9][.]d files for bad init script links; 
# --------------------------------------------------------------------

echo "checking init script links ..."
for folder in /etc/rc[0-9S][.]d; do
	echo "... ${folder}"
	for file in ${folder}/*; do
		if [ ! -f ${file} ]; then
			echo "... ${file} is broken." 
		fi
	done	
done

# ====================================================================
#  
# --------------------------------------------------------------------

exit 0  

