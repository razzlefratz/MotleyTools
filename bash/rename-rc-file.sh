#!/bin/bash
# file: /home/build/cmassoc-tools-1.4.3/bash/swap-daemon.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
#
# --------------------------------------------------------------------

  if [ -z ${1} ]; then
	echo "usage: $(basename ${0}) old_name new_name"
	exit 1
elif [ -z ${2} ]; then
	echo "usage: $(basename ${0}) old_name new_name"
	exit 1
elif [ ! -f /etc/init.d/${1} ]; then
	echo "... create /etc/init/${1} first."
	exit 1
fi

# ====================================================================
#
# --------------------------------------------------------------------

for file in /etc/rc[0-9S].d/[KS][0-9][0-9]${1}; do
	name=$(dirname ${file})/${2}
	ln -fs ../init.d/${2} ${name} 
	rm -f ${file} 
done

