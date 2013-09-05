#!/bin/bash
# file: /usr/local/bin/cmassoc/permissions.sh

# ====================================================================
# symbols;
# --------------------------------------------------------------------

OWNER=root
GROUP=cvs

# ====================================================================
#
# --------------------------------------------------------------------

if [ -z "${1}" ]; then
	echo "No folder given."
	exit 1
fi

# ====================================================================
# recursively set folder and files ownership and permissions;
# --------------------------------------------------------------------

# quotes are needed when filenames contain spaces as on samba shares;

for file in "${1}"/*; do
	echo ${file}
	if [ -d "${file}" ]; then
		chown ${OWNER}:${GROUP} "${file}"
		chmod 6775 "${file}"
		${0} "${file}"
	else
		chown ${OWNER}:${GROUP} "${file}"
		chmod 0775 "${file}"
	fi
done

