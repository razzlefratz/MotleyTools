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
#	install -m ${MAN_PERM} -o ${OWNER} -g ${GROUP} ${PAGES} ${MAN}
library: 
#	install -m ${DIR_PERM} -o ${OWNER} -g ${GROUP} -d ${BIN}
install: compile library
#	install -m ${BIN_PERM} -o ${OWNER} -g ${GROUP} ${TOOLS} ${BIN}
compare:
uninstall:
	cd ${BIN}; rm -fv ${TOOLS}
	cd ${MAN}; rm -fv ${PAGES}
fresh: clean compile
clean:
	rm -f ${GLOBAL} ${TOOLS} ${TRASH}
	chmod ${RUN_PERM} Makefile *.mak *.sh 
	chmod ${SRC_PERM} *.cpp *.hpp *.txt 
check:
	${SH} classes.sh
ignore:
	echo ${TOOLS} | tr " " "\n" > .gitignore


# ====================================================================
# files;
# --------------------------------------------------------------------

include ../classes/classes.mak

