#!/usr/bin/make -f
# file: Makefile
# Published 2005 by Charles Maier Associates Limited for internal use;

# ===================================================================
# folders;
# -------------------------------------------------------------------

FOLDERS=cmassoc calc chrlib clang crypt date ether files libgen link linux list math menu nodes regex scan sort stdio stdlib chrlib string strlib sv tidy tools tree

# ===================================================================
# targets;
# -------------------------------------------------------------------

compile install scripts manuals uninstall fresh clean check ignore:
	@for folder in ${FOLDERS}; do ${MAKE} -C $${folder} ${@}; if [ $${?} -ne 0 ]; then exit 1; fi; done


