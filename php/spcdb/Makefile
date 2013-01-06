#!/usr/bin/make -f
# file: motleytools/php/Makefile
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
#
# --------------------------------------------------------------------

CMTOOLS	:= /usr/local/bin/cmassoc
CMADMIN	:= /usr/local/sbin/cmassoc
MODULES	:=  
TRASH	:= *~ t.* *[.][0-9][0-9][0-9]

# ====================================================================
#
# --------------------------------------------------------------------

.PHONEY: compile scripts manuals install clean

compile:
	mysql --exec="source spcdb.sql;" --password=letmein

scripts:

manuals:

install: compile scripts manuals

clean:
	rm -f ${TRASH}

