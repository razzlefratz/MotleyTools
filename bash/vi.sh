#!/bin/bash
# file: vi.sh
# Published 2007 by Charles Maier Associates Limited for internal use;

# ====================================================================
#
# --------------------------------------------------------------------

for file in ${1}; do
	vi ${file}
done

