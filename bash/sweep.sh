#!/bin/bash
# file: /usr/local/bin/cmassoc/sweep.sh
# published 2004 by charles maier associates limited for internal use;

# ====================================================================
#
# --------------------------------------------------------------------

  if [ -z ${1} ]; then
	syslog -eb ${0} "target folder is undefined."
	exit 1
elif [ -z ${2} ]; then
	syslog -eb ${0} "master folder is undefined."
	exit 1
elif [ ! -d ${1} ]; then
	syslog -eb ${0} "folder ${1} does not exist or is not a folder."
	exit 1
elif [ ! -d ${2} ]; then
	syslog -eb ${0} "folder ${2} does not exist or is not a folder."
	exit 1
elif [ ${1} == ${2} ]; then
	syslog -eb ${0} "folders are the same."
	exit 1
fi

# ====================================================================
#
# --------------------------------------------------------------------

for file in ${1}/*; do
        filename=$(basename ${file})
	if [ -f ${2}/${filename} ]; then
		rm -v ${1}/${filename} 
	fi 
done

# ====================================================================
# finish;
# --------------------------------------------------------------------

exit 0
