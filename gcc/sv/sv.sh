#!/bin/bash
# file: sv/sv.sh

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c sv_ascii.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_clib.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_coper.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_country.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_cplus.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_cproc.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_css.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_cword.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_digit.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_f77.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_fattr.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_glyph.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_html_attr.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_html.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_idl.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_odl.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_ps.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_python.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_shire.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_signals.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_sort.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_state.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_testsort.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_tld.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_tp.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_vb6.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv_zip.c
gcc -Wall -Wextra -Wno-unused-parameter -c sv.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.sv

