# =
# link source files;
# -
deque.o: deque.c link.h
enque.o: enque.c link.h
finditem.o: finditem.c link.h
freeitem.o: freeitem.c link.h
link.o: link.c link.h stackclear.c stackpop.c stackpush.c stacksize.c
makeitem.o: makeitem.c link.h tools.h
queue.o: queue.c link.h
stackclear.o: stackclear.c link.h
stackpop.o: stackpop.c link.h
stackpush.o: stackpush.c link.h tools.h
stacksize.o: stacksize.c link.h
walklist.o: walklist.c link.h
walkloop.o: walkloop.c link.h
# =
# link header files;
# -
link.h:
	touch ../link/${@}
