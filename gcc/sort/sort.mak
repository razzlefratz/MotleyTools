# ====================================================================
# sort source files;
# --------------------------------------------------------------------

hsort.o: hsort.c sort.h
isort.o: isort.c sort.h
psort.o: psort.c sort.h
qsort.o: qsort.c sort.h
sift.o: sift.c sort.h
ssort.o: ssort.c sort.h
swap.o: swap.c sort.h
vfinal.o: vfinal.c sort.h
vfirst.o: vfirst.c sort.h
vindex.o: vindex.c sort.h

# ====================================================================
# sort header files;
# --------------------------------------------------------------------

sort.h: 
	touch ../sort/${@}

