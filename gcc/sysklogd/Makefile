#!/usr/bin/make -f
# file: sysklogd/Makefile

# ====================================================================
# folders;
# --------------------------------------------------------------------

../make.def

# ====================================================================
# symbols;
# --------------------------------------------------------------------

CC=gcc
CFLAGS=-Wall -Wextra -Wno-unused-parameter -DMAKEFILE
LFLAGS=-s
VPATH=../tools:../linux:../strlib
TRASH=*.o t t.* *.log *~ *.orig *.[0-9][0-9][0-9]
DAEMONS=syslogd klogd
MANUAL5=syslog.conf.5
MANUAL8=syslogd.8 klogd.8

# ====================================================================
# targets;
# --------------------------------------------------------------------

all compile: ${DAEMONS}
library:
	install -m 0755 -o ${OWNER} -g ${GROUP} -d ${BIN}
scripts: compile
	install -m 0755 -o ${OWNER} -g ${GROUP} ${ETC}/syslogd ${ETC}/klogd ${DIR}
manuals:
	install -m 0644 -o ${OWNER} -g ${GROUP} ${MANUAL5} ${MAN}/man5
	install -m 0644 -o ${OWNER} -g ${GROUP} ${MANUAL8} ${MAN}/man8
install1: all compile library
	install -m 0755 -o ${OWNER} -g ${GROUP} ${DAEMONS} ${SYS}
	install -m 0755 -o ${OWNER} -g ${GROUP} syslog.conf /etc
	${DIR}/syslogd restart
	${DIR}/klogd restart
	${DIR}/cron restart
#	${SYS}/syslogd
uninstall:
	rm -fv ${SYS} ${DAEMONS}
fresh: clean compile
check:
	${SH} sysklogd.sh
clean:
	rm -f ${TRASH} ${DAEMONS}
	chmod 0755 Makefile *.sh
	chmod 0644 *.c *.h

# ====================================================================
# programs;
# --------------------------------------------------------------------

klogd: klogd.o getoptv.o putoptv.o version.o readpf.o writepf.o checkpf.o removepf.o syslog_basic.o ksyms.o kmodsyms.o
syslogd: syslogd.o getoptv.o putoptv.o version.o uintspec.o waitspec.o statement.o trace.o checkpf.o readpf.o writepf.o removepf.o strlwr.o strcut.o stov.o strfbits.o syslog_facility_codes.o syslog_facility_names.o syslog_lookup.o syslog_severity_codes.o syslog_severity_names.o syslogd_broadcast.o syslogd_admin.o syslogd_merge.o syslogd_stop.o syslogd_enumerate.o syslogd_error.o syslogd_print.o syslogd_flag_names.o syslogd_gethost.o syslogd_index.o syslogd_parse.o syslogd_ready.o syslogd_queue.o syslogd_start.o syslogd_state.o syslogd_scrub.o syslogd_type_names.o syslogd_write.o syslogd_unix_socket.o syslogd_inet_socket.o syslogd_open_sockets.o syslogd_read_sockets.o syslogd_close_sockets.o strfpri.o getsocketname.c sockspec.c hostspec.c emalloc.o hexvalue.o

# ====================================================================
# includes;
# --------------------------------------------------------------------

include ../sysklogd/sysklogd.mak
include ../tools/tools.mak
include ../linux/linux.mak
include ../files/files.mak
include ../strlib/strlib.mak
include ../date/date.mak

