# ====================================================================
# source files;
# --------------------------------------------------------------------

filepart.o: filepart.c files.h types.h
pathpart.o: pathpart.c files.h types.h
cfopen.o: cfopen.c files.h
fileexists.o: fileexists.c files.h
fileinfolder.o: fileinfolder.c tools.h files.h
fileinstring.o: fileinstring.c files.h
fileinvector.o: fileinvector.c files.h
filelist.o: filelist.c tools.h ../strlib/strlib.h files.h ../list/list.h
filepart.o: filepart.c files.h 
find.o: find.c files.h find.h
findfile.o: findfile.c types.h files.h find.h
fopenparent.o: fopenparent.c files.h
fopensearch.o: fopensearch.c files.h
fullpath.o: fullpath.c files.h
isdotdir.o: isdotdir.c types.h files.h
makefind.o: makefind.c files.h find.h
makepath.o: makepath.c files.h
match.o: match.c files.h
mergepath.o: mergepath.c files.h
open1.o: open1.c files.h
open2.o: open2.c files.h
partfile.o: partfile.c files.h
partpath.o: partpath.c files.h
path.o: path.c fullpath.c makepath.c splitpath.c mergepath.c
pathpart.o: pathpart.c files.h 
plain.o: plain.c types.h
setfiletype.o: setfiletype.c files.h
showfind.o: showfind.c find.h types.h
splitpath.o: splitpath.c files.h
vfopen.o: vfopen.c files.h


# ====================================================================
# header files;
# --------------------------------------------------------------------

files.h: types.h
	touch ../files/${@}
find.h: types.h
	touch ../files/${@}

