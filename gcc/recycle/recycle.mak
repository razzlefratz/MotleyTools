# ====================================================================
# source files;
# --------------------------------------------------------------------

recycle.o: recycle.c recycle.h tools.h getoptv.h putoptv.h linux.h 
scanargs.o: scanargs.c recycle.h
scanlogset.o: scanlogset.c recycle.h strlib.h sizes.h
scansize.o: scansize.c recycle.h
scandaily.o: scandaily.c recycle.h
scanmonthly.o: scanmonthly.c recycle.h
scanweekly.o: scanweekly.c recycle.h weekdays.h strlib.h
scancreate.o: scancreate.c recycle.h chars.h
scanscript.o: scanscript.c recycle.h tools.h
keywords.o: keywords.c keywords.h
findstate.o: findstate.c recycle.h
makestate.o: makestate.c recycle.h
readconfig.o: readconfig.c recycle.h keywords.h tools.h chars.h sizes.h linux.h strlib.h date.h file.h error.h
readstate.o: readstate.c recycle.h sizes.h
writestate.o: writestate.c recycle.h date.h
copyfile.o: copyfile.c recycle.h
due.o: due.c recycle.h date.h

# ====================================================================
# header files;
# --------------------------------------------------------------------

keywords.h:
	touch ../recycle/${@}
recycle.h: types.h sizes.h flags.h
	touch ../recycle/${@}

