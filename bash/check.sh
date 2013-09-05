#!/bin/bash
# file: check.sh
# Published 2004 by Charles Maier Associates Limited for internal use;

# ======================================================================
#  
# ----------------------------------------------------------------------

if [ -z $PKG_CONFIG_PATH ]; then 
	echo symbol PKG_CONFIG_PATH is undefined
	exit 1
elif [ -z $LD_LIBRARY_PATH ]; then 
	echo symbol LD_LIBRARY_PATH is undefined
	exit 1
elif [ -z ${src} ]; then
	echo symbol {src} is undefined
	exit 1
elif [ -z ${cfg} ]; then
	echo symbol {cfg} is undefined
	exit 1
elif [ -z ${tbd} ]; then 
	echo symbol {tbd} is undefined
	exit 1
elif [ -z ${hlp} ]; then
	echo symbol {hlp} is undefined
	exit 1
elif [ ! -d ${src} ]; then
	echo folder ${src} does not exist
	exit 1
elif [ ! -d ${cfg} ]; then
	echo folder ${cfg} does not exist
	exit 1
elif [ ! -d ${tbd} ]; then
	echo folder ${tbd} does not exist
	exit 1
elif [ ! -f ${log} ]; then
	echo file ${log} does not exist
	exit 1
elif [ ! -d ${lfs} ]; then
	echo folder ${lfs} does not exist
	exit 1
else
	echo {src}=${src}
	echo {cfg}=${cfg}
	echo {hlp}=${hlp}
	echo {tbd}=${tbd}
	echo {lfs}=${lfs}
	echo {log}=${log}
fi

# ======================================================================
#  
# ----------------------------------------------------------------------

exit 0

