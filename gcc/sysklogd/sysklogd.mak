# ====================================================================
# source files;
# --------------------------------------------------------------------

klogd.o: klogd.c ksyms.h getoptv.h version.h types.h pidfile.h
getoptv.o: getoptv.c getoptv.h putoptv.h version.h sizes.h
putoptv.o: putoptv.c getoptv.h putoptv.h
version.o: version.c version.h
readpf.o: readpf.c pidfile.h
writepf.o: writepf.c pidfile.h
removepf.o: removepf.c pidfile.h
checkpf.o: checkpf.c pidfile.h
syslog-base.o: syslog-base.c syslog.h paths.h sizes.h types.h flags.h files.h
ksyms.o: ksyms.c ksyms.h
kmodsyms.o: kmodsyms.c ksyms.h
syslog.o: syslog.c syslog.h getoptv.h putoptv.h version.h tools.h types.h flags.h sizes.h date.h
syslog_facility_codes.o: syslog_facility_codes.c syslog.h types.h
syslog_severity_codes.o: syslog_severity_codes.c types.h syslog.h
syslog_encode.o: syslog_encode.c syslog.h types.h
syslog_decode.o: syslog_decode.c syslog.h types.h
syslog_lookup.o: syslog_lookup.c syslog.h types.h
syslogd.o: syslogd.c syslog.h syslogd.h getoptv.h tools.h flags.h linux.h pidfile.h strlib.h date.h
uintspec.o: uintspec.c tools.h
waitspec.o: waitspec.c tools.h
statement.o: statement.c tools.h
trace.o: trace.c
removepidfile.o: removepidfile.c pidfile.h
strlwr.o: strlwr.c strlib.h
strcut.o: strcut.c strlib.h
stov.o: stov.c strlib.h tools.h
strfbits.o: strfbits.c strlib.h types.h flags.h
strfpri.o: strfpri.c syslog.h syslogd.h types.h flags.h
syslog_facility_names.o: syslog_facility_names.c syslog.h syslogd.h
syslog_severity_names.o: syslog_severity_names.c syslog.h syslogd.h
syslogd_broadcast.o: syslogd_broadcast.c syslogd.h broadcast.h tools.h types.h sizes.h
syslogd_admin.o: syslogd_admin.c syslogd.h strlib.h version.h tools.h types.h
syslogd_merge.o: syslogd_merge.c syslogd.h tools.h flags.h
syslogd_stop.o: syslogd_stop.c syslogd.h version.h types.h
syslogd_enumerate.o: syslogd_enumerate.c syslog.h syslogd.h
syslogd_error.o: syslogd_error.c syslogd.h types.h
syslogd_print.o: syslogd_print.c syslogd.h types.h
syslogd_flag_names.o: syslogd_flag_names.c syslogd.h
syslogd_gethost.o: syslogd_gethost.c syslog.h syslogd.h
syslogd_index.o: syslogd_index.c syslog.h syslogd.h flags.h
syslogd_parse.o: syslogd_parse.c syslog.h syslogd.h flags.h
syslogd_ready.o: syslogd_ready.c syslog.h syslogd.h flags.h
syslogd_queue.o: syslogd_queue.c syslogd.h strlib.h types.h flags.h date.h
syslogd_start.o: syslogd_start.c syslogd.h strlib.h version.h tools.h types.h
syslogd_state.o: syslogd_state.c syslogd.h strlib.h flags.h types.h date.h
syslogd_scrub.o: syslogd_scrub.c syslogd.h flags.h
syslogd_type_names.o: syslogd_type_names.c syslogd.h
syslogd_write.o: syslogd_write.c syslogd.h tools.h flags.h strlib.h
syslogd_unix_socket.o: syslogd_unix_socket.c syslog.h syslogd.h types.h
syslogd_inet_socket.o: syslogd_inet_socket.c syslog.h syslogd.h types.h
syslogd_open_sockets.o: syslogd_open_sockets.c syslog.h syslogd.h
syslogd_read_sockets.o: syslogd_read_sockets.c syslog.h syslogd.h
syslogd_close_sockets.o: syslogd_close_sockets.c syslog.h syslogd.h

# ====================================================================
# header files;
# --------------------------------------------------------------------

syslogd.h: syslog.h paths.h types.h sizes.h trace.h
	touch ../sysklogd/${@}

