#!/usr/local/bin make -f
# file: recycle/Makefile

# ====================================================================
# environment;
# --------------------------------------------------------------------

include ../make.def

# ====================================================================
# folders;              
# --------------------------------------------------------------------

BIN=/usr/local/bin/cmassoc
MAN=/usr/share/man/man8
DIR=/etc/recycle.d

# ====================================================================
# symbols;              
# --------------------------------------------------------------------

CFLAGS=-Wall -Wextra -Wno-unused-parameter -DMAKEFILE
LFLAGS=-s -lpopt
VPATH=../tools:../files:../linux:../strlib:../chrlib:../date
TRASH=*.exe *.obj *.o t t.* *~ *.[0-9][0-9][0-9]
TOOLS=recycle
PAGES=recycle.8

# ====================================================================
# targets;
# --------------------------------------------------------------------

all compile: ${TOOLS}
scripts:
	install -m 6775 -o ${OWNER} -g ${GROUP} -d ${DIR}
manuals:
	install -m 0644 -o ${OWNER} -g ${GROUP} ${PAGES} ${MAN}
library:
	install -m 0755 -o ${OWNER} -g ${GROUP} -d ${BIN} ${DIR}
install: all compile library
	install -m 0755 -o ${OWNER} -g ${GROUP} ${TOOLS} ${BIN}
	install -m 0440 -o ${OWNER} -g ${GROUP} recycle.conf /etc
uninstall:
	cd ${BIN}; rm -fv ${TOOLS}
	cd ${MAN}; rm -fv ${PAGES}
	rm -frv ${DIR} /etc/recycle.conf
fresh: clean compile
clean:
	rm -f ${TRASH} ${TOOLS}
	chmod 0755 Makefile *.sh
	chmod 0644 *.c *.h
check:
	${SH} recycle.sh
ignore:
	echo ${TOOLS} | tr " " "\n" > .gitignore

# ====================================================================
# programs;             
# --------------------------------------------------------------------

recycle: console.o recycle.o readconfig.o strargv.o copyfile.o readstate.o writestate.o findstate.o makestate.o due.o keywords.o weekdays.o runscript.o pathpart.o filepart.o match.o emalloc.o datecomp.o svfirst.o svindex.o svorder.o scanargs.o scanlogset.o scancreate.o scansize.o scanmonthly.o scanweekly.o scandaily.o scanscript.o error.o error_on_line.o daytime.o eprintf.o

# ====================================================================
# includes;              
# --------------------------------------------------------------------

include ../tools/tools.mak
include ../linux/linux.mak
include ../files/files.mak
include ../chrlib/chrlib.mak
include ../strlib/strlib.mak
include ../date/date.mak
