#!/usr/bin/make -f
# file: bash/Makefile
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# environment;
# --------------------------------------------------------------------

include ../make.def

# ====================================================================
# symbols;
# --------------------------------------------------------------------

ADMIN=ssh-keys.sh ubuntu.sh update.sh
BUILD=definitions.sh directories.sh distributed.sh environment.sh permissions.sh
ROOTONLY=mount.sh remount.sh unmount.sh ssh-rsa-perms.sh
BOOTONLY=
TOOLS=fetch.sh lockout.sh mkpatch.sh package.sh packup.sh save.sh sweep.sh unpack.sh show.sh unver.sh vi-all.sh
TRASH=*~ *[.][0-9][0-9][0-9] t t.*

# ====================================================================
# targets;
# --------------------------------------------------------------------

all:
compile:
library:
	install -m ${DIR_PERM} -o ${OWNER} -g ${GROUP} -d ${BIN}
scripts: library
	install -m ${RUN_PERM} -o ${OWNER} -g ${GROUP} ${ADMIN} ${ROOTONLY} ~
manuals:
install: scripts
	if [ -d /etc/profile.d ]; then install -m ${BIN_PERM} -o ${OWNER} -g ${GROUP} motley-tools.sh /etc/profile.d; fi
uninstall:
	rm -fv ${BIN}/*.sh 
	cd ~; rm -fv ${ADMIN} ${BUILD} ${ROOTONLY}
fresh:
check:
clean:
	rm -f ${TRASH}

