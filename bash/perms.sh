#!/bin/bash
# Published 2005 by Charles Maier Associates Limited for internal use;

# ====================================================================
# 
# --------------------------------------------------------------------

IFS=":"

# ====================================================================
# 
# --------------------------------------------------------------------

  if [ -z ${1} ]; then
	echo "usage: $(basename ${0}) file [file] [...]"
	exit 1
elif [ ! -f ${1} ]; then
	echo "${1} does not exist or is not a folder."
	exit 1
fi

# ====================================================================
# 
# --------------------------------------------------------------------

echo ${1}
exec 9>&0 <${1}
while read type mode owner group files; do
	for file in ${files}; do
		echo ${file}
		if [ -f ${file} ]; then
			if [ ${type} == 'F' ]; then
				chown ${owner}:${group} ${file}
				chmod ${mode} ${file}
				continue
			fi
			echo "${file} is not a regular file."
		elif [ -d ${file} ]; then
			if [ ${type} == 'D' ]; then
				chown ${owner}:${group} ${file}
				chmod ${mode} ${file}
				continue
			fi
			echo "${file} is not a folder."
		elif [ -p ${file} ]; then
			if [ ${type} == 'P' ]; then
				chown ${owner}:${group} ${file}
				chmod ${mode} ${file}
				continue
			fi
			echo "${file} is not a pipe."
		elif [ -L ${file} ]; then
			if [ ${type} == 'L' ]; then
				chown ${owner}:${group} ${file}
				chmod ${mode} ${file}
				continue
			fi
			echo "${file} is not a link."
		elif [ -S ${file} ]; then
			if [ ${type} == 'S' ]; then
				chown ${owner}:${group} ${file}
				chmod ${mode} ${file}
				continue
			fi
			echo "${file} is not a socket."
		else
			echo "${file} is missing or misplaced."
		fi
	done
done
exec 0>&9 9>&-
