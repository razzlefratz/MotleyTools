# ====================================================================
# files;
# --------------------------------------------------------------------

_filename.o: _filename.c files.h types.h
_pathname.o: _pathname.c files.h types.h
broadcast.o: broadcast.c broadcast.h linux.h tools.h types.h sizes.h
checkpf.o: checkpf.c pidfile.h
datecomp.o: datecomp.c date.h
daytime.o: daytime.c date.h
emalloc.o: emalloc.c tools.h types.h
erealloc.o: erealloc.c tools.h types.h
error.o: error.c types.h error.h
error_at_line.o: error_at_line.c types.h error.h
event.o: event.c types.h error.h
getoptv.o: getoptv.c getoptv.h putoptv.h version.h sizes.h
getprocname.o: getprocname.c linux.h sizes.h types.h
getusername.o: getusername.c linux.h types.h
hostspec.o: hostspec.c tools.h sizes.h strlib.h types.h
makefind.o: makefind.c files.h find.h types.h
makepath.o: makepath.c files.h types.h
match.o: match.c tools.h types.h
mergepath.o: mergepath.c files.h types.h
midnight.o: midnight.c date.h
partfile.o: partfile.c files.h types.h
partpath.o: partpath.c files.h types.h
procname.o: procname.c linux.h sizes.h types.h
putoptv.o: putoptv.c getoptv.h putoptv.h
readpf.o: readpf.c pidfile.h types.h
removepf.o: removepf.c pidfile.h
runscript.o: runscript.c paths.h types.h flags.h sizes.h
setumask.o: setumask.c linux.h chrlib.h types.h chars.h
showfind.o: showfind.c find.h types.h
signal_codes.o: signal_codes.c signals.h types.h
signal_names.o: signal_names.c
signals.o: signals.c signals.h types.h
signalspec.o: signalspec.c signals.h types.h
sockspec.o: sockspec.c tools.h sizes.h strlib.h types.h
splitpath.o: splitpath.c files.h types.h
statement.o: statement.c tools.h types.h
stov.o: stov.c strlib.h tools.h types.h
strargv.o: strargv.c strlib.h chrlib.h types.h chars.h
strcut.o: strcut.c strlib.h types.h
getsocketname.o: getsocketname.c
strfbits.o: strfbits.c strlib.h types.h flags.h
strfpid.o: strfpid.c linux.h sizes.h types.h
strlwr.o: strlwr.c strlib.h types.h
strsplit.o: strsplit.c strlib.h types.h
svfirst.o: svfirst.c strlib.h types.h
svindex.o: svindex.c strlib.h types.h
svorder.o: svorder.c strlib.h types.h
syslog_error.o: syslog_error.c syslog.h sizes.h types.h
syslog_error_at_line.o: syslog_error_at_line.c syslog.h sizes.h types.h
syslog_event.o: syslog_event.c syslog.h sizes.h types.h
timespec.o: timespec.c tools.h types.h
trace.o: trace.c
uintspec.o: uintspec.c tools.h types.h
userid.o: userid.c tools.h types.h
username.o: username.c linux.h sizes.h types.h
version.o: version.c version.h
waitspec.o: waitspec.c tools.h types.h
weekdays.o: weekdays.c weekdays.h
writepf.o: writepf.c pidfile.h

# ====================================================================
# files;
# --------------------------------------------------------------------

chars.h chrtype.h date.h flags.h paths.h sizes.h types.h trace.h weekdays.h nls.h:
	touch ../include/${@}
broadcast.h: types.h
	touch ../include/${@}
chrlib.h: types.h chars.h
	touch ../include/${@}
file.h: types.h
	touch ../include/${@}
files.h: types.h
	touch ../include/${@}
find.h: types.h
	touch ../include/${@}
getoptv.h putoptv.h version.h:
	touch ../include/${@}
linux.h: types.h
	touch ../include/${@}
pidfile.h procstat.h set.h:
	touch ../include/${@}
signals.h: types.h
	touch ../include/${@}
strlib.h: types.h
	touch ../include/${@}
tools.h: types.h
	touch ../include/${@}

