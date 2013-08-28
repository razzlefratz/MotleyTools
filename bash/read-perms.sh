#!/bin/bash
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# 
# --------------------------------------------------------------------

IFS=':'

# ====================================================================
# 
# --------------------------------------------------------------------

if [ -z ${1} ]; then
	echo "usage: $(basename ${0}) file"
	exit 1
elif [ ! -r ${1} ]; then
	echo "${1} is missing or misplaced or not readable."
	exit 1
fi

# ====================================================================
# read /etc/fstab;
# --------------------------------------------------------------------

exec 9>&0 <${1}
while read type mode owner group files; do 
	for file in ${files}; do
		echo ${file}
		case ${type} in
			F)
				if [ -f ${file} ]; then
					chown ${owner}:${group} ${file}
					chmod ${mode} ${file}
				else
					echo "${file} is not a regular file."
				fi
				;;
			D)
				if [ -d ${file} ]; then
					chown ${owner}:${group} ${file}
					chmod ${mode} ${file}
				else
					echo "${file} is not folder."
				fi
				;;
			P)
				if [ -p ${file} ]; then
					chown ${owner}:${group} ${file}
					chmod ${mode} ${file}
				else
					echo "${file} is not a pipe."
				fi
				;;
			L)
				if [ -L ${file} ]; then
					chown ${owner}:${group} ${file}
					chmod ${mode} ${file}
				else
					echo "${file} is not a link."
				fi
				;;
			S)
				if [ -S ${file} ]; then
					chown ${owner}:${group} ${file}
					chmod ${mode} ${file}
				else
					echo "${file} is not a socket."
				fi
				;;
			*)
				echo "syntax error: ${type}:${mode}:${owner}:${group}:${files}"
				;;
		esac
	done
done
exec 0>&9 9>&-
