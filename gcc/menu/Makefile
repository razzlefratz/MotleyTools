#!/bin/make -f
# file: menu/Makefile

# ====================================================================
# environment;
# --------------------------------------------------------------------

include ../make.def

# ====================================================================
# symbols;
# --------------------------------------------------------------------

CFLAGS=-Wall -Wextra -Wno-unused-parameter -DMAKEFILE 
LFLAGS=
VPATH=../menu:../tools
TRASH=*.exe *.obj *.o t t.c *~ *.[0-9][0-9][0-9]
TOOLS=menu
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
cygwin: compile
	cp ${TOOLS} ${BIN}
uninstall:
	cd ${BIN}; rm -fv ${TOOLS}
	cd ${MAN}; rm -fv ${PAGES}
fresh: clean compile
check:
	${SH} menu.sh
clean:
	rm -f ${TRASH} ${TOOLS}
	chmod 0755 Makefile *.sh
	chmod 0644 *.c *.h

# ====================================================================
# files;
# --------------------------------------------------------------------

menu: menu.o getoptv.o putoptv.o version.o emalloc.o error.o menudefine.o menulookup.o menuprefix.o menuload.o menudump.o menushow.o menusize.o menulist.o

# ====================================================================
# files;
# --------------------------------------------------------------------

include ../menu/menu.mak

