#!/bin/bash
libs="stdio stdlib stddef string ctype stream fstream"
for file in *; do
	if [ -d ${file} ]; then
		folder=$(basename ${file})
		cd ${folder}
		for name in ${libs}; do
			change *.cpp *.hpp \
				-e "<${name}.h>" \
				-t "<c${name}>" \
				-c
		done
		cd ..
	fi
done
