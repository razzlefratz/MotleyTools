#!/bin/bash
# file: php/php-prop.sh
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
#
# --------------------------------------------------------------------

while [ ${#} != 0 ]; do
	echo "# ="
	echo "# " 
	echo "# -"
	echo
	echo "\tfunction get${1} ()"
	echo "\t{"
	echo "\t\treturn (\$this->${1});"
	echo "\t}"
	echo
	echo "\tfunction set${1} (\$value)"
	echo "\t{"
	echo "\t\t\$this->${1} = \$value;"
	echo "\t\treturn;"
	echo "\t}"
	echo
	shift
done

