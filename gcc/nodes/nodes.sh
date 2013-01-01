#!/bin/bash
# file: nodes/nodes.h

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c _xmlattribute.c
gcc -Wall -Wextra -Wno-unused-parameter -c _xmlvalue.c
gcc -Wall -Wextra -Wno-unused-parameter -c htmlscan.c
gcc -Wall -Wextra -Wno-unused-parameter -c nodes.c
gcc -Wall -Wextra -Wno-unused-parameter -c nodesize.c
gcc -Wall -Wextra -Wno-unused-parameter -c reorder.c
gcc -Wall -Wextra -Wno-unused-parameter -c xmlnode.c
gcc -Wall -Wextra -Wno-unused-parameter -c xmlattribute.c
gcc -Wall -Wextra -Wno-unused-parameter -c xmlcontent.c
gcc -Wall -Wextra -Wno-unused-parameter -c xmledit.c
gcc -Wall -Wextra -Wno-unused-parameter -c xmlelement.c
gcc -Wall -Wextra -Wno-unused-parameter -c xmlfree.c
gcc -Wall -Wextra -Wno-unused-parameter -c xmlindent.c
gcc -Wall -Wextra -Wno-unused-parameter -c xmlopen.c
gcc -Wall -Wextra -Wno-unused-parameter -c xmlread.c
gcc -Wall -Wextra -Wno-unused-parameter -c xmlsample.c
gcc -Wall -Wextra -Wno-unused-parameter -c xmlscan.c
gcc -Wall -Wextra -Wno-unused-parameter -c xmlschema.c
gcc -Wall -Wextra -Wno-unused-parameter -c xmlstream.c
gcc -Wall -Wextra -Wno-unused-parameter -c xmltree.c
gcc -Wall -Wextra -Wno-unused-parameter -c xmlvalue.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.o

