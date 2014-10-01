# ====================================================================
# regex source files;
# --------------------------------------------------------------------

regexcomp.o: regexcomp.c tools.h regex.h
regexfree.o: regexfree.c regex.h
regexhelp.o: regexhelp.c regex.h
regexmake.o: regexmake.c tools.h regex.h chrlib.h
regexmax.o: regexmax.c regex.h
regexmin.o: regexmin.c regex.h
regexscan.o: regexscan.c regex.h
regexshow.o: regexshow.c regex.h
regexspan.o: regexspan.c regex.h

# ====================================================================
# regex header files;
# --------------------------------------------------------------------

regex.h: tools.h types.h flags.h
	touch ../regex/${@}

