#!/bin/bash
# file: /usr/local/bin/checkvalue.sh
# Published 2004 by Charles Maier Associates Limited for internal use;

# ====================================================================
#
# --------------------------------------------------------------------

if [ -z ${1} ]; then
	echo "usage: $(basename ${0}) file label value"
        exit 1
elif [ ! -f ${1} ]; then
	echo "file ${1} does not exist or is not a folder."
        exit 1
elif [ -z ${2} ]; then
	echo "label field is missing."
        exit 1
elif [ -z ${3} ]; then
	echo "value field is missing."
        exit 1
fi

# ====================================================================
#
# --------------------------------------------------------------------

label=${2}
value="/^${label}/ { print \$2 }"
value=$(mawk "${value}" ${1} )
# value=$(mawk -v pattern=${2} '/^$pattern/ { print \$2 }' ${1})
value=$(echo -n ${value})

# ====================================================================
#
# --------------------------------------------------------------------

if [ -z ${value} ]; then
	echo "empty? ${1} ${label}"
        exit 1
elif [ ${value} != ${3} ]; then
	echo "wrong! ${1} ${label} ${value}"
        exit 1
else
	echo "right. ${1} ${label} ${value}"
	exit 0
fi

