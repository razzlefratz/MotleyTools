#!/bin/bash
# file: cmassoc-tools.sh

# ====================================================================
#
# --------------------------------------------------------------------

CHARLIE=/media/CHARLIE/linux
LIBRARY=root@appslinux01.intellon.com
PACKAGE=cmassoc-tools-1.6.0 

# ====================================================================
#
# --------------------------------------------------------------------

echo -n "package [${PACKAGE}]: "; read
if [ ! -z ${REPLY} ]; then
	PACKAGE=${REPLY}
fi

# ====================================================================
#
# --------------------------------------------------------------------

ARCHIVE=${PACKAGE}.tar.gz
if [ -f ${CHARLIE}/${ARCHIVE} ]; then
	cp ${CHARLIE}/${ARCHIVE} .
else
	echo -n "library [${LIBRARY}]: "; read
	if [ ! -z ${REPLY} ]; then
		LIBRARY=${REPLY}
	fi
	echo -n "download [yes/no]: "; read
	if [ "${REPLY}" == "yes" ]; then
		scp ${LIBRARY}:${PWD}/${ARCHIVE} .
	fi
fi

# ====================================================================
#
# --------------------------------------------------------------------

if [ ! -f ${ARCHIVE}.tar.gz ]; then
	rm -fr ${PACKAGE}
	tar -vzxf ${ARCHIVE}
	cd ${PACKAGE}
	make clean
	make install 2> install.log
	make manuals 2> manuals.log
	cd ..
fi

# ====================================================================
#
# --------------------------------------------------------------------

echo -n "cleanup [yes/no]: "; read
if [ "${REPLY}" == "yes" ]; then
	rm -fr ${PACKAGE}
	rm -f ${ARCHIVE}
fi
