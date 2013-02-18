#!/usr/bin/make -f
# file: cmassoc-tools/Makefile
# Published 2005 by Charles Maier Associates Limited for internal use;

# ===================================================================
# environment;
# -------------------------------------------------------------------

ARCHIVE := ..
PRIVATE := /Volumes/CHARLIE
CONTROL := /home/ftp/linux/system/src/custom
PACKAGE	:= $(basename ${PWD})
EXCLUDE := --exclude=.git 
FOLDERS := awk bash php python bash gcc gcpp 
FOLDERS := gcc gcpp 

# ===================================================================
# pseudo targets;
# -------------------------------------------------------------------

.PHONY: all compile install scripts manuals uninstall check fresh clean
.PHONY: archive private control nightly

# ===================================================================
# common targets;
# -------------------------------------------------------------------

compile install scripts manuals uninstall check fresh clean ignore:
	for folder in ${FOLDERS}; do ${MAKE} -C $${folder} ${@}; if [ $${?} -ne 0 ]; then exit 1; fi; done

# ===================================================================
# snapshot targets;
# -------------------------------------------------------------------

nightly: clean 
	if [ -d ${ARCHIVE} ]; then tar ${EXCLUDE} -vzcf ${ARCHIVE}/$$(date +%y%m%d-%H%M%S).tar.gz  -C .. ${PACKAGE}; fi
	if [ -d ${PRIVATE} ]; then tar ${EXCLUDE} -vzcf ${PRIVATE}/$$(date +%y%m%d-%H%M%S).tar.gz  -C .. ${PACKAGE}; fi

snapshot: clean 
	if [ -d ${ARCHIVE} ]; then tar ${EXCLUDE} -vzcf ${ARCHIVE}/$$(stamp).tar.gz  -C .. ${PACKAGE}; fi
	if [ -d ${PRIVATE} ]; then tar ${EXCLUDE} -vzcf ${PRIVATE}/$$(stamp).tar.gz  -C .. ${PACKAGE}; fi

archive: clean 
	if [ -d ${ARCHIVE} ]; then tar ${EXCLUDE} -vjcf ${ARCHIVE}/${PACKAGE}.tar.bz2 -C .. ${PACKAGE}; fi
	if [ -d ${ARCHIVE} ]; then tar ${EXCLUDE} -vzcf ${ARCHIVE}/${PACKAGE}.tar.gz  -C .. ${PACKAGE}; fi 

private: clean
	if [ -d ${PRIVATE} ]; then tar ${EXCLUDE} -vjcf ${PRIVATE}/${PACKAGE}.tar.bz2 -C .. ${PACKAGE}; fi
	if [ -d ${PRIVATE} ]; then tar ${EXCLUDE} -vzcf ${PRIVATE}/${PACKAGE}.tar.gz  -C .. ${PACKAGE}; fi

control: 
	if [ -d ${CONTROL} ]; then tar ${EXCLUDE} -vjcf ${CONTROL}/${PACKAGE}.tar.bz2 -C .. ${PACKAGE}; fi 
	if [ -d ${CONTROL} ]; then tar ${EXCLUDE} -vzcf ${CONTROL}/${PACKAGE}.tar.gz  -C .. ${PACKAGE}; fi
	
