#!/bin/bash
# =
#
# -
if [ -z ${1} ]; then
	echo "No version given."
	exit 1
fi
# =
#
# -
for file in *.${1}; do
	mv ${file} $(basename ${file} .${1})
done 
