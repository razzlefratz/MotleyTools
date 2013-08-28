#!/bin/bash
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
#
# --------------------------------------------------------------------

if [ -z ${1} ]; then
	echo "${0}: No folder specified."
	exit 1
elif [ ! -d ${1} ]; then
	echo "${0}: Folder ${1} does not exist or is not a folder."
	exit 1
fi

# ====================================================================
#
# --------------------------------------------------------------------

for file in ${1}/*
do
	if [ -d ${file} ]; then
		name=$(basename ${file})
        	if [ ${name} == "init.d" ]; then
			echo ${file}
			chmod 2755 $file
        	elif [ ${name} == "src" ]; then
			echo ${file}
			chmod 2755 $file
		elif [ ${name} == "etc" ]; then
			echo ${file}
			chmod 2755 $file
		elif [ ${name} == "usr" ]; then
			echo ${file}
			chmod 2755 $file
		fi
		${0} ${file}
	fi
done
