#!/bin/bash
# Published 2006 by Charles Maier Associates Limited for internal use;

# ====================================================================
#
# --------------------------------------------------------------------

for file in ${1}/*; do
	if [ -d ${file} ]; then
		echo "<h2>"${file}"</h2>"
		${0} ${file}
	else
		echo "\t<li>"$(basename ${file})"</li>"
	fi
done

