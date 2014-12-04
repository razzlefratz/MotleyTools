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
TOOLS= Topology.cgi Identity.cgi Security.cgi Priority.cgi Firmware.cgi cgiecho.cgi
PAGES= Topology.html Identity.html Security.html Priority.html Firmware.html

# ====================================================================
# targets;
# --------------------------------------------------------------------

all compile: ${TOOLS}
scripts:
manuals:
install: all compile library
#	install -m 4555 -o ${OWNER} -g ${GROUP} ${TOOLS} ${BIN}
library:
#	install -m 6775 -o ${OWNER} -g ${GROUP} -d ${BIN}
uninstall:
	cd ${BIN}; rm -fv ${TOOLS}
	cd ${WWW}; rm -fv ${PAGES}
fresh: clean compile
clean:
	rm -f ${TRASH} ${TOOLS}
	chmod 0755 Makefile *.mak *.sh
	chmod 0644 *.c *.h
check:
	${SH} ./html.sh
ignore:
	echo ${TOOLS} | tr " " "\n" > .gitignore

# ====================================================================
# rules;
# --------------------------------------------------------------------

%.cgi: %.o
	${CC} ${LFLAGS} -o ${@} ${^}

# ====================================================================
#  
# --------------------------------------------------------------------

cgiecho.cgi: cgiecho.o head.o styles.o foot.o menu.o unit.o getoptv.o putoptv.o version.o hexstring.o hexdecode.o todigit.o output.o error.o cgistov.o styles.o head.o foot.o

Topology.cgi: Topology.o head.o output.o styles.o foot.o menu.o unit.o select.o textbox.o
Identity.cgi: Identity.o head.o output.o styles.o foot.o menu.o unit.o select.o textbox.o
Security.cgi: Security.o head.o output.o styles.o foot.o menu.o unit.o select.o checkbox.o
Priority.cgi: Priority.o head.o output.o styles.o foot.o menu.o unit.o select.o checkbox.o
Firmware.cgi: Firmware.o head.o output.o styles.o foot.o menu.o unit.o select.o checkbox.o

# ====================================================================
# files;
# --------------------------------------------------------------------

include ../tools/tools.mak
include ../html/html.mak

