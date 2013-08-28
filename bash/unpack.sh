#!/bin/bash
# file: /usr/local/bin/cmassoc/unpack.sh
# Published 2004 by Charles Maier Associates Limited for internal use;

# ====================================================================
# 
# --------------------------------------------------------------------

. /etc/default/definitions.sh

# ====================================================================
# 
# --------------------------------------------------------------------

if [ ! -z ${2} ]; then
	src=${src}/${2}
fi

# ====================================================================
# 
# --------------------------------------------------------------------

  if [ -z ${1} ]; then 
	syslog -eb ${0} "package name is not defined."
	exit 1
elif [ -z ${src} ]; then
	syslog -eb ${0} "symbol {src} is not defined."
	exit 1
elif [ -z ${tbd} ]; then
	syslog -eb ${0} "symbol {tbd} is not defined."
	exit 1 
elif [ ! -d ${src} ]; then
	syslog -eb ${0} "folder ${src} does not exist or is not a folder."
	exit 1
elif [ ! -d ${tbd} ]; then
	syslog -eb ${0} "folder ${tbd} does not exist or is not a folder."
	exit 1
elif [ -f ${src}/${1}.tar ]; then
	tar -C ${tbd} -vxf ${tbd} ${src}/${1}.tar
	exit 0 
elif [ -f ${src}/${1}.tgz ]; then
	tar -C ${tbd} -vzxf ${src}/${1}.tgz
	exit 0
elif [ -f ${src}/${1}.tar.gz ]; then
	tar -C ${tbd} -vzxf ${src}/${1}.tar.gz
	exit 0
elif [ -f ${src}/${1}.tar.bz2 ]; then
	tar -C ${tbd} -vjxf ${src}/${1}.tar.bz2
	exit 0
elif [ -f ${src}/${1}.tar.tar ]; then
	tar -C ${tbd} -vjxf ${src}/${1}.tar.tar
	exit 0
elif [ -f ${src}/${1}.* ]; then
	syslog -eb ${0} "package ${1} may have wrong extension."
	exit 0
else
	syslog -eb ${0} "package ${1} does not exist or is not a folder."
	exit 1
fi

# ====================================================================
# finish;
# --------------------------------------------------------------------

exit 0

