#!/bin/bash

# ====================================================================
#
# --------------------------------------------------------------------

if [ -d ${1} ]; then
	for file in ${2}; do 
		if [ -f ${1}/${file} ]; then
			ln -fs ${1}/${file}
		fi
	done
fi

