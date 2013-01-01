# file: scan/scan.mak

# ====================================================================
# files;
# --------------------------------------------------------------------

copytoken.o: copytoken.c scan.h types.h
copyquote.o: copyquote.c scan.h types.h
havebreak.o: havebreak.c scan.h types.h
haveclass.o: haveclass.c scan.h types.h
havematch.o: havematch.c scan.h types.h
havetoken.o: havetoken.c scan.h types.h
isbreak.o: isbreak.c scan.h types.h
isclass.o: isclass.c scan.h types.h
ismatch.o: ismatch.c scan.h types.h
isready.o: isready.c scan.h types.h
istoken.o: istoken.c scan.h types.h
nextbreak.o: nextbreak.c scan.h types.h
nexttoken.o: nexttoken.c scan.h types.h
scanalnum.o: scanalnum.c scan.h types.h
scanalpha.o: scanalpha.c scan.h types.h
scanblank.o: scanblank.c scan.h types.h
scanblock.o: scanblock.c scan.h types.h
scanblockmatch.o: scanblockmatch.c scan.h types.h
scanbreak.o: scanbreak.c scan.h types.h
scanbreakmatch.o: scanbreakmatch.c scan.h types.h
scanchunk.o: scancntrl.c scan.h types.h
scancntrl.o: scancntrl.c scan.h types.h
scandigit.o: scandigit.c scan.h types.h
scanflush.o: scanflush.c scan.h types.h
scangroup.o: scangroup.c scan.h types.h
scaninput.o: scaninput.c scan.h types.h
scanlimit.o: scanlimit.c scan.h types.h
scanprint.o: scanprint.c scan.h types.h
scanquote.o: scanquote.c scan.h types.h
scanquotematch.o: scanquotematch.c scan.h types.h
scanreset.o: scanreset.c scan.h types.h
scanspace.o: scanspace.c scan.h types.h
scanstart.o: scanstart.c scan.h types.h
scantoken.o: scantoken.c scan.h chars.h types.h
scanuntil.o: scanuntil.c scan.h types.h
scanuntilmatch.o: scanuntilmatch.c scan.h types.h
scanwhile.o: scanwhile.c scan.h types.h
scanwhilematch.o: scanwhilematch.c scan.h types.h
scanwrite.o: scanwrite.c scan.h types.h
showtoken.o: showtoken.c scan.h types.h
tokensize.o: tokensize.c scan.h types.h
tokentext.o: tokentext.c scan.h types.h
tokentype.o: tokentype.c scan.h types.h

# ====================================================================
# files;
# --------------------------------------------------------------------

scan.h: types.h
	touch ../scan/${@}

