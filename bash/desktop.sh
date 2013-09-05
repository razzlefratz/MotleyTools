#!/bin/bash
# file: /usr/local/bin/cmassoc/desktop.sh
# Published 2004 by Charles Maier Associates Limited for internal use;

# ====================================================================
# check freedesktop.org environment variables;  
# --------------------------------------------------------------------

  if [ -z ${XDG_CACHE_HOME} ]; then
	echo symbol XDG_CACHE_HOME is not defined.
	exit 1
elif [ -z ${XDG_CONFIG_HOME} ]; then
	echo symbol XDG_CONFIG_HOME is not defined.
	exit 1
elif [ -z ${XDG_CONFIG_DIRS} ]; then
	echo symbol XDG_CONFIG_DIRS is not defined.
	exit 1
elif [ -z ${XDG_DATA_HOME} ]; then
	echo symbol XDG_DATA_HOME is not defined.
	exit 1
elif [ -z ${XDG_DATA_DIRS} ]; then
	echo symbol XDG_DATA_DIRS is not defined.
	exit 1
else
	echo XDG_CACHE_HOME=${XDG_CACHE_HOME} >> ${log}
	echo XDG_CONFIG_HOME=${XDG_CONFIG_HOME} >> ${log}
	echo XDG_CONFIG_DIRS=${XDG_CONFIG_DIRS} >> ${log}
	echo XDG_DATA_HOME=${XDG_CONFIG_HOME} >> ${log}
	echo XDG_DATA_DIRS=${XDG_CONFIG_DIRS} >> ${log}
fi

# ====================================================================
# check environment variables and environment; create folders;  
# --------------------------------------------------------------------

install -m 0755 -o root -g root -d ${XDG_CONFIG_HOME}
install -m 0755 -o root -g root -d ${XDG_DATA_HOME}

# ====================================================================
# finish;
# --------------------------------------------------------------------

exit 0

