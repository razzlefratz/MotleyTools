#!/bin/make -f
# file: demo/Makefile

# ====================================================================
# environment;
# --------------------------------------------------------------------

include ../make.def

# ====================================================================
# symbols;
# --------------------------------------------------------------------

CFLAGS=-Wall -Wextra -Wno-unused-parameter -DMAKEFILE
LFLAGS=
VPATH=../demo
TRASH=*.exe *.obj *.o t t.c *~ *.[0-9][0-9][0-9]
TOOLS=
PAGES=

# ====================================================================
# rules;
# --------------------------------------------------------------------

all compile:
scripts:
manuals:
	install -m 0444 -o ${OWNER} -g ${GROUP} ${PAGES} ${MAN}
library:
	install -m 6775 -o ${OWNER} -g ${GROUP} -d ${BIN}
install: all compile library
	install -m 0755 -o ${OWNER} -g ${GROUP} ${TOOLS} ${BIN}
	install -m 4755 -o ${OWNER} -g ${GROUP} ${SYSTEM} ${BIN}
uninstall:
	cd ${BIN}; rm -fv ${TOOLS}
	cd ${MAN}; rm -fv ${PAGES}
fresh: clean compile
clean:
	rm -f ${TRASH} ${TOOLS}
	chmod 0755 Makefile *.sh
	chmod 0644 *.c 
check:
#	${SH} demo.sh
ignore:
	echo ${TOOLS} | tr " " "\n" > .gitignore

# ====================================================================
# files;
# --------------------------------------------------------------------

include ../demo/demo.mak

