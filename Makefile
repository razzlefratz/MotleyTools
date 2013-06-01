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

.PHONY: all compile install scripts manuals uninstall fresh clean check ignore
.PHONY: archive private control nightly

# ===================================================================
# common targets;
# -------------------------------------------------------------------

compile install scripts manuals uninstall fresh clean check ignore:
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

# ===================================================================
#  
# -------------------------------------------------------------------

PAGES=afm.7 align.7 argv.7 b64.7 bang.7 bin2hex.7 blank.7 calend.7 call.7 case.7 catalog.7 cblock.7 cbrief.7 cdep.7 cedit.7 change.7 chr.7 cinc.7 cmerge.7 crlf.7 csv2html.7 ctar.7 define.7 defix.7 delta.7 detab.7 detag.7 dls.7 dmp2hex.7 ds.7 efru.7 efsu.7 enbrace.7 enfix.7 englyph.7 entab.7 envp.7 fbar.7 ff.7 filesize.7 footer.7 fp.7 grab.7 graph.7 grope.7 hbrief.7 header.7 hex.7 hex2bin.7 hexcmp.7 hexdmp.7 html.7 ifd.7 import.7 key.7 l2p.7 lam.7 localhost.7 log.7 loop.7 matrix.7 mp.7 mrg.7 munge.7 nics.7 np.7 ocomp.7 odc.7 odd.7 ode.7 odump.7 odx.7 oedit.7 offset.7 order.7 paginate.7 preamble.7 quiet.7 relate.7 remove.7 respond.7 rex.7 runjobs.7 sbrief.7 search.7 shakey.7 shakeys.7 shout.7 sign.7 single.7 sizeof.7 solicit.7 space.7 srt.7 stamp.7 sv.7 sweep.7 symlinks.7 timer.7 tls.7 toolkit.7 tr.7 trim.7 try.7 typelist.7 unique.7 vl.7 vu.7 what.7 whom.7 wl.7 xde.7 xml.7 cfm.7 csstidy.7 ctidy.7 htmltidy.7 javatidy.7 mptidy.7 phptidy.7 

# ===================================================================
#  
# -------------------------------------------------------------------

unman:
	for page in ${PAGES}; do rm -vfr /usr/share/man/man7/$${page}; done

