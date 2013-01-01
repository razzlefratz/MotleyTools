# ====================================================================
# source files;
# --------------------------------------------------------------------

broadcast.o: broadcast.c broadcast.h linux.h tools.h types.h sizes.h
checkpf.o: checkpf.c pidfile.h
ftype.o: ftype.c linux.h
getgroupname.o: getgroupname.c linux.h
getprocname.o: getprocname.c linux.h sizes.h
getusername.o: getusername.c linux.h
getviewport.o: getviewport.c linux.h
groupname.o: groupname.c linux.h sizes.h
isscript.o: isscript.c linux.h types.h
lsb-filename.o: lsb-filename.c
printk.o: printk.c
procname.o: procname.c linux.h sizes.h
readpf.o: readpf.c pidfile.h types.h
removepf.o: removepf.c pidfile.h
runscript.o: runscript.c linux.h paths.h sizes.h
set-fileflag.o: set-fileflag.c
setumask.o: setumask.c linux.h chrlib.h
signal_codes.o: signal_codes.c signals.h
signal_names.o: signal_names.c
signal_codes.o: signal_codes.c signals.h
signal_names.o: signal_names.c
signals.o: signals.c signals.h tools.h
signalspec.o: signalspec.c signals.h
sockaddrout.o: sockaddrout.c packet_ll.h
spawn.o: spawn.c tools.h files.h linux.h
statement.o: statement.c tools.h
strfaddr.o: strfaddr.c
strfpid.o: strfpid.c linux.h sizes.h
sv_signals.o: sv_signals.c
syslog_basic.o: syslog_basic.c syslog.h paths.h sizes.h types.h flags.h 
syslog_error.o: syslog_error.c syslog.h sizes.h types.h
syslog_error_at_line.o: syslog_error_at_line.c syslog.h sizes.h types.h
userid.o: userid.c tools.h convert.h
username.o: username.c linux.h sizes.h
writepf.o: writepf.c pidfile.h


# ====================================================================
# header files;
# --------------------------------------------------------------------

broadcast.h: types.h
	touch ../linux/${@}
linux.h: types.h
	touch ../linux/${@}
network.h: types.h
	touch ../linux/${@}
pidfile.h set.h:
	touch ../linux/${@}
signals.h: types.h
	touch ../linux/${@}
syslog.h: types.h
	touch ../linux/${@}

