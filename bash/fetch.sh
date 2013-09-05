#!/bin/bash
# file: /home/cmaier/build/fetch.sh
# Published 2007 by Charles Maier Associates Limited for internal use;

# ====================================================================
#
# --------------------------------------------------------------------

  if [ -z ${1} ]; then
	echo "No Package Specified."
	exit 1
elif [ -c ${2} ]; then
	echo "No Version Specified."
	exit 1
fi
# ====================================================================
#
# --------------------------------------------------------------------

LIBRARY=ftp://pong/intellon/software
SCRATCH=/home/cmaier/build
PACKAGE=${1}
VERSION=${2}
RELEASE=${PACKAGE}-${VERSION}
ARCHIVE=${RELEASE}.tar.gz

# ====================================================================
#
# --------------------------------------------------------------------

cd ${SCRATCH}
wget ${LIBRARY}/${PACKAGE}/${ARCHIVE}
tar -zxf ${ARCHIVE}
cd ${SCRATCH}/${RELEASE}
make install
cd ${SCRATCH}
rm -r ${ARCHIVE}

