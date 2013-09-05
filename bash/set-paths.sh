#!/bin/bash
# file: /set-paths.sh
# Published 2006 by Charles Maier Associates Limited for internal use;

# ====================================================================
# path for super users;
# --------------------------------------------------------------------

if [ ${UID} == 0 ]; then
	for FOLDER in \
		/sbin \
		/usr/sbin \
		/usr/local/sbin \
		/usr/gnome/sbin \
		/usr/X11R6/sbin \
		/usr/X11R7/sbin \
		/opt/sbin 
	do
		if [ -d ${FOLDER} ]; then
			PATH=${PATH}:${FOLDER}
		fi
	done
fi

# ====================================================================
# path for normal users
# --------------------------------------------------------------------

for FOLDER in \
	/bin \
	/usr/bin \
	/usr/local/bin \
	/usr/local/bin/cmassoc \
	/usr/local/bin/intellon \
	/usr/gnome/bin \
	/usr/X11R6/bin \
	/usr/X11R7/bin \
	/opt/bin
do
	if [ -d ${FOLDER} ]; then
		PATH=${PATH}:${FOLDER}
	fi
done

# ====================================================================
# 
# --------------------------------------------------------------------

PATH=${PATH}:.
echo ${PATH}

