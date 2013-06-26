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
install: 
	@if [ -d /etc/profile.d ]; then install -m 0775 -o root -g root motley-tools.sh /etc/profile.d; fi;
library:
uninstall:
	@if [ -d /etc/profile ]; then rm -fr /etc/profile.d/motley-tools.sh; fi;
fresh: clean compile
clean:
	rm -f ${TRASH} 
	chmod 0755 Makefile *.sh
	chmod 0644 ${FILES} 
	chmod 0644 *.txt 
check:
	${SH} misc.sh
ignore:
	echo ${TOOLS} | tr " " "\n" > .gitignore

# ====================================================================
# targets;
# --------------------------------------------------------------------

# ====================================================================
# files;
# --------------------------------------------------------------------

