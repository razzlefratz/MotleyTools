#!/bin/bash
# file:/usr/local/bin/cmassoc/show.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# display specified logfile   
# --------------------------------------------------------------------

if [ -z ${1} ]; then
	footer -l 100 /var/log/system.log
else
	footer -l 100 /var/log/${1}.log
fi

