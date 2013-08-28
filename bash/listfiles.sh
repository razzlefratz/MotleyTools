#!/bin/sh
# file: listfiles.sh

# ====================================================================
#
# --------------------------------------------------------------------

if [ -z ${1} ]; then
	echo "usage: ${@} dir"
	exit 1
fi

# ====================================================================
# list files under the specified folder;
# --------------------------------------------------------------------

echo ${1}
for file in ${1}/*; do
	if [ ${file} == "." ]; then
		continue
	elif [ ${file} == ".." ]; then
		continue 
	elif [ -d ${file} ]; then
		${0} ${file}
	else
		echo "   $(basename ${file})"
	fi
done

