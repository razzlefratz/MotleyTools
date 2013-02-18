# ====================================================================
#
# --------------------------------------------------------------------

BIN=/home/www/intellon
LIB=/usr/local/lib
INC=/usr/local/include

# ====================================================================
#
# --------------------------------------------------------------------

CFLAGS=-g -Wall
CC=gcc
AR=ar
RANLIB=ranlib
LIBS=-L./ -lcgic

# ====================================================================
#
# --------------------------------------------------------------------

all: libcgic.a cgictest.cgi capture

install: libcgic.a
	install -m 4555 -o 0 -g 0 libcgic.a ${LIB}
	install -m 0444 -o 0 -g 0 cgic.h ${INC}
	install -m 4555 -o 0 -g 0 cgictest.cgi ${BIN}

libcgic.a: cgic.o cgic.h
	rm -f libcgic.a
	$(AR) rc libcgic.a cgic.o
	$(RANLIB) libcgic.a

#mingw32 and cygwin users: replace .cgi with .exe

cgictest.cgi: cgictest.o libcgic.a
	gcc cgictest.o -o cgictest.cgi ${LIBS}

capture: capture.o libcgic.a
	gcc capture.o -o capture ${LIBS}

clean:
	rm -f *.o *.a *.[0-9][0-9][0-9] cgictest.cgi capture

