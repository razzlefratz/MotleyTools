#!/bin/bash
# file: /usr/local/bin/cmassoc/save.sh
# Published 2004 by Charles Maier Associates Limited for internal use;

# ====================================================================
#
# --------------------------------------------------------------------

if [ -z ${1} ]; then 
	syslog -eb ${0} "package is undefined."
	exit 1
elif [ -z ${tbd} ]; then 
	syslog -eb ${0} "symbol {tbd} is undefined."
	exit 1 
elif [ -z ${src} ]; then 
	syslog -eb ${0} "symbol {src} is undefined."
	exit 1 
elif [ ! -d ${tbd} ]; then 
	syslog -eb ${0} "folder ${tbd} does not exist or is not a folder."
	exit 1 
elif [ ! -d ${src} ]; then 
	syslog -eb ${0} "folder ${src} does not exist or is not a folder."
	exit 1
elif [ ! -d ${tbd}/${1} ]; then
	syslog -eb ${0} "folder ${1} does not exist or is not a folder."
	exit 1 
fi

# ====================================================================
#
# --------------------------------------------------------------------

tar -vjcf ${1}.tar.bz2 ${1}
mv ${1}.tar.bz2 ${src}/${1}.tar.bz2 
tar -vzcf ${1}.tar.gz ${1}
mv ${1}.tar.gz ${src}/${1}.tar.gz 
# rm -fr ${1}

# ====================================================================
# finish;
# --------------------------------------------------------------------

exit 0

