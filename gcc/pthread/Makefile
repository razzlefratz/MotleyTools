# ====================================================================
#
# --------------------------------------------------------------------

lflags=-lpthread
MODULES=pthread-hello pthread-multi pthread-detach pthread-mutex pthread-variable

# ====================================================================
#
# --------------------------------------------------------------------

all: ${MODULES}

# ====================================================================
#
# --------------------------------------------------------------------

pthread-hello: pthread-hello.c
	${CC} -o ${@} ${^} ${lflags}

pthread-multi: pthread-multi.c
	${CC} -o ${@} ${^} ${lflags}

pthread-detach: pthread-detach.c
	${CC} -o ${@} ${^} ${lflags}

pthread-mutex: pthread-mutex.c
	${CC} -o ${@} ${^} ${lflags}

pthread-variable: pthread-variable.c
	${CC} -o ${@} ${^} ${lflags}

# ====================================================================
#
# --------------------------------------------------------------------

clean:
	rm -f ${MODULES} *.o *~ *.[0-9][0-9][0-9]
ignore:
	echo ${TOOLS} | tr " " "\n" > .gitignore

