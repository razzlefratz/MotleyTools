#!/bin/make -f
# file: widgets/Makefile

# ====================================================================
# folders;
# --------------------------------------------------------------------

include ../make.def

# ====================================================================
# symbols;
# --------------------------------------------------------------------

VPATH=../tools
TRASH=*.exe *.obj *.o t t.c *~ *.[0-9][0-9][0-9] 
TOOLS=MyApp
PAGES=

# ====================================================================
# targets;
# --------------------------------------------------------------------

all: compile install
compile: ${TOOLS}
scripts:
manuals:
	install -m 0444 -o ${OWNER} -g ${GROUP} ${PAGES} ${MAN}
library: 
	install -m 2755 -o ${OWNER} -g ${GROUP} -d ${BIN}
install: compile library
#	install -m 0555 -o ${OWNER} -g ${GROUP} ${TOOLS} ${BIN}
compare:
uninstall:
	cd ${BIN}; rm -fv ${TOOLS}
	cd ${MAN}; rm -fv ${PAGES}
clean:
	rm -f ${GLOBAL} ${TOOLS} ${TRASH}
fresh: clean compile

# ====================================================================
# 
# --------------------------------------------------------------------

MyApp: MyApp.o MyFrame.o

# ====================================================================
# files;
# --------------------------------------------------------------------

include ../widgets/widgets.mak


