#!/bin/bash
# file: /etc/default/distributed.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# start distributed c compiler (distcc) if available;
# --------------------------------------------------------------------

if [ -x /usr/local/bin/distcc ]; then
	echo -n "use distributed c compiler [no]: "
	read answer
        if [ -z ${answer} ]; then
		answer=no
	fi
	if [ ${answer} == "yes" ]; then
		echo ... using distcc with 8 processors >> ${log}
		PATH=/etc/alternatives:${PATH}
		alias make='make -j 8 CC=distcc'
	elif [ $(uname -m) == "i686" ]; then
		echo ... using distcc with 4 processors >> ${log}
		alias make='make -j 4'
	else
		echo ... using distcc with 2 processors >> ${log}
		alias make='make -j 2'
	fi
elif [ $(uname -m) == "i686" ]; then
	echo ... using distcc with 4 processors >> ${log}
	alias make='make -j 4'
else
	echo ... using distcc with 2 processors >> ${log}
	alias make='make -j 2'
fi

# ====================================================================
#  
# --------------------------------------------------------------------

