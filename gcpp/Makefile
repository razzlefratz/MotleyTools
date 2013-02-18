#!/usr/bin/make -f
# file: gcpp/Makefile
# Published 2005 by Charles Maier Associates Limited for intenal use;

# ===================================================================
# folders;
# -------------------------------------------------------------------

FOLDERS=programs classes

# ===================================================================
# targets;
# -------------------------------------------------------------------

compile install scripts manuals uninstall fresh clean check ignore:
	@for folder in ${FOLDERS}; do ${MAKE} -C $${folder} ${@}; if [ $${?} -ne 0 ]; then exit 1; fi; done


