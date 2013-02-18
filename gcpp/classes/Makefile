#!/bin/make -f
# file: classes/Makefile

# ====================================================================
# folders;
# --------------------------------------------------------------------

include ../make.def

# ====================================================================
# symbols;
# --------------------------------------------------------------------

VPATH=../classes
TRASH=*.exe *.obj *.o t t.c *~ *.[0-9][0-9][0-9] 
TOOLS=
PAGES=

# ====================================================================
# targets;
# --------------------------------------------------------------------

all: compile install compare
compile: 
scripts:
manuals:
#	install -m 0444 -o ${OWNER} -g ${GROUP} ${PAGES} ${MAN}
library: 
	install -m 2755 -o ${OWNER} -g ${GROUP} -d ${BIN}
install: compile library
#	install -m 0755 -o ${OWNER} -g ${GROUP} ${TOOLS} ${BIN}
compare:
uninstall:
	cd ${BIN}; rm -fv ${TOOLS}
	cd ${MAN}; rm -fv ${PAGES}
fresh: clean compile
clean:
	rm -f ${GLOBAL} ${TOOLS} ${TRASH}
check:
	${SH} classes.sh
ignore:
	echo ${TOOLS} | tr " " "\n" > .gitignore


# ====================================================================
# files;
# --------------------------------------------------------------------

include ../classes/classes.mak

