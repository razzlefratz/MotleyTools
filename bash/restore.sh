#!/bin/bash
# =
#
# -
version=.001
for file in *${version}; do
	new=$(basename ${file})
	old=$(basename ${file} ${version})
	mv -v ${new} ${old}
done
