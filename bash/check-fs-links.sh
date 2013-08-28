#!/bin/bash
# file: /usr/local/bin/cmassoc/chec-fs-links.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# check CMLinux filesystem links;
# --------------------------------------------------------------------

echo "checking CMLinux filesystem links ..."
for file in /*; do
	if [ -L ${file} ]; then
		echo "... ${file}"
		case ${file} in
		/libexec)
			if [ ! ${file} -ef /sbin ]; then
				echo "... /libexec should link to /sbin"
			fi
			;;
		/share)
			if [ ! ${file} -ef /usr${file} ]; then
				echo "... ${file} should link to /usr${file}"
			fi
			;;
		/doc|/info|/man)
			if [ ! ${file} -ef /usr/share${file} ]; then
				echo "... ${file} should link to /usr/share${file}"
			fi
			;;
		*) 
			echo "... link ${file} should not exist."
		esac
	fi
done

# ====================================================================
#
# --------------------------------------------------------------------

exit 0

