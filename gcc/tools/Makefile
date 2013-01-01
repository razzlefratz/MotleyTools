#!/bin/make -f
# file: tools/Makefile

# ====================================================================
# environment;
# --------------------------------------------------------------------

include ../make.def

# ====================================================================
# symbols;
# --------------------------------------------------------------------

CFLAGS=-Wall -Wextra -Wno-unused-parameter -DMAKEFILE
LFLAGS=
VPATH=../tools
TRASH=*.exe *.obj *.o t t.c *~ *.[0-9][0-9][0-9]
TOOLS=
PAGES=

# ====================================================================
# targets;
# --------------------------------------------------------------------

all compile: ${TOOLS}
scripts:
manuals:
#	install -m 0444 -o ${OWNER} -g ${GROUP} ${PAGES} ${MAN}
install: all compile library
#	install -m 0755 -o ${OWNER} -g ${GROUP} ${TOOLS} ${BIN}
library:
#	install -m 6775 -o ${OWNER} -g ${GROUP} -d ${BIN}
uninstall:
	cd ${BIN}; rm -fv ${TOOLS}
	cd ${MAN}; rm -fv ${PAGES}
fresh: clean compile
check:
	${SH} tools.sh
clean:
	rm -f ${TRASH} ${TOOLS}
	chmod 0755 Makefile *.sh
	chmod 0644 *.c *.h
	touch version.h

# ====================================================================
# files;
# --------------------------------------------------------------------

include ../tools/tools.mak

