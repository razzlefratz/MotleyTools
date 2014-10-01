# ====================================================================
# chrlib source files;
# --------------------------------------------------------------------

charset.o: charset.c tools.h chrlib.h regex.h chrtype.h
chrcount.o: chrcount.c chrlib.h
chrdef.o: chrdef.c chrlib.h regex.h
chresc.o: chresc.c chrlib.h
chrescmap.o: chrescmap.c chrlib.h
chrhex.o: chrhex.c convert.h memory.h chrlib.h
chrindex.o: chrindex.c chrlib.h
chrlib.o: chrlib.c chrtype.c chrdef.c chresc.c chrhex.c chrindex.c chrcount.c chrtable.c chrlwr.c chroct.c chrset.c chrsub.c chruesc.c chrupr.c ctoascii.c ctocntrl.c ctoupper.c ctolower.c ctoprint.c
chrlwr.o: chrlwr.c chrlib.h strlib.h
chroct.o: chroct.c convert.h chrlib.h
chrset.o: chrset.c chrlib.h
chrsub.o: chrsub.c chrlib.h
chrtbl.o: chrmap.c chrlib.h
chrtable.o: chrtable.c chrlib.h
chrtype.o: chrtype.c chrtype.h
chruesc.o: chruesc.c chrlib.h
chruescmap.o: chruescmap.c chrlib.h
chrupr.o: chrupr.c chrlib.h strlib.h
ct_ascii.o: ct_ascii.c
ct_ebcdic.o: ct_ebcdic.c
ct_fname.o: ct_fname.c
ctoascii.o: ctoascii.c chrtype.h
ctocntrl.o: ctocntrl.c chrtype.h
ctolower.o: ctolower.c chrtype.h
ctoprint.o: ctoprint.c chrtype.h
ctoupper.o: ctoupper.c chrtype.h
ctodigit.o: ctodigit.c chrtype.h
cursor.o: cursor.c tools.h types.h sizes.h

# ====================================================================
# chrlib source files;
# --------------------------------------------------------------------

chrlib.h: chars.h types.h
	touch ../chrlib/${@}

ascii.h charset.h chrname.h chrtype.h:
	touch ../chrlib/${@}

