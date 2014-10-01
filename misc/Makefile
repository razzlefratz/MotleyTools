#!bin/make -f
# file: cmassoc/Makefile
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# environment;
# --------------------------------------------------------------------

include ../make.def

# ====================================================================
# symbols;
# --------------------------------------------------------------------

FILES = CERTIFICATE LICENSE
TRASH = *.[0-9][0-9][0-9] 

# ====================================================================
# targets;
# --------------------------------------------------------------------

all:
compile:
scripts:
manuals:
library:
install: 
	@if [ -d /etc/profile.d ]; then install -m ${BIN_PERM} -o ${OWNER} -g ${GROUP} motley-tools.sh /etc/profile.d; fi;
uninstall:
	@if [ -d /etc/profile.d ]; then rm -fr /etc/profile.d/motley-tools.sh; fi;
fresh: clean compile
clean:
	rm -f ${TRASH} 
	chmod ${RUN_PERM} Makefile *.sh
	chmod ${SRC_PERM} ${FILES} 
check:
	${SH} misc.sh
ignore:
#	echo ${FILES} | tr " " "\n" > .gitignore

