#!/bin/bash
# Published 2007 by Charles Maier Associates Limited for internal use;

# ====================================================================
#
# --------------------------------------------------------------------

  if [ -z ${1} ]; then
	echo "No package specified."
	exit 1
elif [ -z ${2} ]; then
	echo "No version specified."
	exit 1
elif [ ! -d /usr/local/bin/cmassoc ]; then
	echo "Motley Tools are missing"
	exit 1
fi

# ====================================================================
#
# --------------------------------------------------------------------

LIBRARY=/home/ftp/intellon/software
SCRATCH=/home/cmaier/build
PACKAGE=${1}
VERSION=${2}
SECTION=${LIBRARY}/${PACKAGE}
RELEASE=${PACKAGE}-${VERSION}

# ====================================================================
#
# --------------------------------------------------------------------

cd ${RELEASE}
make clean
chown -R nobody:nobody *
for file in *.*; do
	if [ -d ${file} ]; then
		chmod 6755 ${file}
		chmod 0755 ${file}/Makefile ${file}/*.sh
		crlf Makefile *.mak ${file}*.sh 
		crlf ${file}/*.c ${file}/*.h 
		touch ${file}/*
	fi
done
make clean
cd ${SCRATCH}

# ====================================================================
#
# --------------------------------------------------------------------

tar -zcf ${SECTION}/${RELEASE}.tar.gz  ${RELEASE}
tar -jcf ${SECTION}/${RELEASE}.tar.bz2 ${RELEASE}


