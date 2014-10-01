# ====================================================================
# strlib source files;
# --------------------------------------------------------------------

ischarset.o: ischarset.c strlib.h
stov.o: stov.c strlib.h tools.h
str2argv.o: str2argv.c strlib.h chars.h
strargv.o: strargv.c strlib.h
strfbin.o: strfbin.c strlib.h number.h
strcap.o: strcap.c strlib.h
strcatn.o: strcatn.c strlib.h
strccmp.o: strccmp.c strlib.h
strcomp.o: strcomp.c strlib.h
strconv.o: strconv.c strlib.h
strcpyn.o: strcpyn.c strlib.h
strcut.o: strcut.c strlib.h
strdcl.o: strdcl.c tree.h tools.h emalloc.c error.c
strdictcmp.o: strdictcmp.c strlib.h
strend.o: strend.c strlib.h
strenv.o: strenv.c strlib.h
strfascii.o: strfascii.c strlib.h
strfbits.o: strfbits.c strlib.h types.h
strfcntrl.o: strfcntrl.c strlib.h
strfcsv.o: strfcsv.c strlib.h
strfglyph.o: strfglyph.c strlib.h
strfhex.o: strfhex.c strlib.h number.h
strfield.o: strfield.c strlib.h
strfietf.o: strfietf.c chrlib.h strlib.h
strfunix.o: strfunix.c chrlib.h strlib.h
stricmp.o: stricmp.c strlib.h
string.o: string.c
strint.o: strint.c strlib.h chrlib.h
strjoin.o: strjoin.c strlib.h
strlcmp.o: strlcmp.c strlib.h
strlwr.o: strlwr.c strlib.h
strmap.o: strmap.c strlib.h
strmerge.o: strmerge.c strlib.h
strmin.o: strmin.c strlib.h
strnchr.o: strnchr.c strlib.h
strnpcat.o: strnpcat.c strlib.h
strnpcpy.o: strnpcpy.c strlib.h
strpart.o: strpart.c strlib.h
strpcat.o: strpcat.c strlib.h
strpcpy.o: strpcpy.c strlib.h
strpfx.o: strpfx.c strlib.h
strpkgcmp.o: strpkgcmp.c strlib.h
strrcpy.o: strrcpy.c strlib.h
strrcut.o: strrcut.c strlib.h
strremove.o: strremove.c strlib.h
strselect.o: strselect.c strlib.h
strsfx.o: strsfx.c strlib.h
strsplit.o: strsplit.c strlib.h
strsub.o: strsub.c strlib.h
strtblcmp.o: strtblcmp.c strlib.h
strtoken.o: strtoken.c strtoken.c
strtrim.o: strtrim.c strlib.h
strucmp.o: strucmp.c strlib.h
struesc.o: struesc.c strlib.h chrlib.h number.h
stov.o: stov.c strlib.h number.h error.h
strupr.o: strupr.c strlib.h
strval.o: strval.c strlib.h
strvercmp.o: strvercmp.c strlib.h
strvis.o: strvis.c strlib.h
strvsplit.o: strvsplit.c strlib.h
strwcmp.o: strwcmp.c strlib.h
strxcmp.o: strxcmp.c strlib.h
svfinal.o: svfinal.c strlib.h
svfirst.o: svfirst.c strlib.h
svindex.o: svindex.c strlib.h
svorder.o: svorder.c tools.h strlib.h
svprint.o: svprint.c

# ====================================================================
# strlib header files;
# --------------------------------------------------------------------

strlib.h: types.h
	touch ../strlib/${@}

