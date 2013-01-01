#!/bin/bash
# file: tree/tree.sh

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c depend.c
gcc -Wall -Wextra -Wno-unused-parameter -c dict.c
gcc -Wall -Wextra -Wno-unused-parameter -c dictdefine.c
gcc -Wall -Wextra -Wno-unused-parameter -c dictlookup.c
gcc -Wall -Wextra -Wno-unused-parameter -c dictreport.c
gcc -Wall -Wextra -Wno-unused-parameter -c dictrevert.c
gcc -Wall -Wextra -Wno-unused-parameter -c edge.c
gcc -Wall -Wextra -Wno-unused-parameter -c editnode.c
gcc -Wall -Wextra -Wno-unused-parameter -c eventree.c
gcc -Wall -Wextra -Wno-unused-parameter -c findnode.c
gcc -Wall -Wextra -Wno-unused-parameter -c freenode.c
gcc -Wall -Wextra -Wno-unused-parameter -c inorder.c
gcc -Wall -Wextra -Wno-unused-parameter -c makenode.c
gcc -Wall -Wextra -Wno-unused-parameter -c pathsort.c
gcc -Wall -Wextra -Wno-unused-parameter -c postorder.c
gcc -Wall -Wextra -Wno-unused-parameter -c preorder.c
gcc -Wall -Wextra -Wno-unused-parameter -c savenode.c
gcc -Wall -Wextra -Wno-unused-parameter -c term.c
gcc -Wall -Wextra -Wno-unused-parameter -c termdefine.c
gcc -Wall -Wextra -Wno-unused-parameter -c termlookup.c
gcc -Wall -Wextra -Wno-unused-parameter -c termreport.c
gcc -Wall -Wextra -Wno-unused-parameter -c tree.c
gcc -Wall -Wextra -Wno-unused-parameter -c treesize.c

# ====================================================================
#
# --------------------------------------------------------------------

rm -f *.o

