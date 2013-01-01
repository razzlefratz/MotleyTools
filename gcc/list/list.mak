# ====================================================================
# functions;
# --------------------------------------------------------------------

list.o: list.c listappend.c listcolumn.c listcreate.c listdefine.c listdelete.c listdetect.c listexpand.c listinsert.c listrubout.c listsort.c liststatus.c
listappend.o: listappend.c list.h
listcolumn.o: listcolumn.c format.h linux.h list.h
listcreate.o: listcreate.c list.h memory.h
listdefine.o: listdefine.c list.h
listdelete.o: listdelete.c list.h
listdetect.o: listdetect.c list.h
listexpand.o: listexpand.c list.h memory.h
listinsert.o: listinsert.c list.h
listload.o: listload.c chars.h files.h list.h tools.h
listremove.o: listremove.c list.h
listrubout.o: listrubout.c list.h
listsort.o: listsort.c list.h
liststatus.o: liststatus.c list.h

# ====================================================================
# includes;
# --------------------------------------------------------------------

list.h: types.h
	touch ../list/${@}

