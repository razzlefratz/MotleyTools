#!/bin/bash
# file: /usr/local/bin/cmassoc/mkpatch.sh
# Published 2004 by Charles Maier Associates Limited for internal use;

# ====================================================================
#
# --------------------------------------------------------------------

# src=${PWD}/src
# tbd=${PWD}

# ====================================================================
#
# --------------------------------------------------------------------

if [ -z ${1} ]; then
	echo usage: ${0} package version tag
	exit 1
elif [ -z ${2} ]; then
	echo usage: ${0} package version tag
	exit 1
elif [ -z ${3} ]; then
	echo usage: ${0} package version tag
	exit 1
elif [ -z ${src} ]; then
	echo symbol {src} is undefined 
	exit 1
elif [ -z ${tbd} ]; then
	echo symbol {tbd} is undefined 
	exit 1
elif [ ! -d ${src} ]; then
	echo folder ${src} does not exist  
	exit 1
elif [ ! -d ${tbd} ]; then
	echo folder ${tbd} does not exist  
	exit 1
elif [ ! -d ${tbd}/${1} ]; then
	echo folder ${tbd}/${1} does not exist  
	exit 1
elif [ ! -d ${tbd}/${1}-orig ]; then
	echo folder ${tbd}/${1}-orig does not exist  
	exit 1
fi

# ====================================================================
# 
# --------------------------------------------------------------------

diff -ru ${1}-orig ${1} > ${src}/${1}-${2}-${3}.patch
vi ${src}/${1}-${2}-${3}.patch

# ====================================================================
# finish
# --------------------------------------------------------------------

ls -la ${src}/${1}-*
exit 1

