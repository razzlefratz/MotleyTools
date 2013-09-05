#!/bin/bash
FONTS=${X11R7}/lib/X11/fonts
for file in ${FONTS}/*; do
	if [ -d ${file} ]; then
		echo $(basename ${0}): ${file}
		mkfontdir ${file}
	fi
done
rm ${FONTS}/fonts.*
