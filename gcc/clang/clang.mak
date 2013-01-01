# ====================================================================
# clang source files;
# --------------------------------------------------------------------

cfooter.o: cfooter.c clang.h
cheader.o: cheader.c clang.h
ccollect.o: ccollect.c clang.h list.h 
cinclude.o: cinclude.c tools.h clang.h files.h list.h scan.h
coper.o: coper.c clang.h
cword.o: cword.c clang.h

# ====================================================================
# clang header files;
# --------------------------------------------------------------------

clang.h: tools.h list.h coper.h cword.h
	touch ../clang/${@}

coper.h cword.h:
	touch ../clang/${@}

