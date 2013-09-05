#!/bin/bash

# ====================================================================
#
# --------------------------------------------------------------------

PACKAGE=int6000-utils-linux
echo -n "Package [${PACKAGE}]: "; read
if [ ! -z ${REPLY} ]; then
	PACKAGE=${REPLY}
fi

# ====================================================================
#
# --------------------------------------------------------------------

rm -fr ${PACKAGE}       
cvs checkout ${PACKAGE}
cd ${PACKAGE}
make install 1> install.log 2> install.err
make manuals
cat install.err

