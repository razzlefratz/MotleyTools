#!/bin/bash
# file: ether/ether.sh

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c IPAddr.c
gcc -Wall -Wextra -Wno-unused-parameter -c IPAout.c
gcc -Wall -Wextra -Wno-unused-parameter -c IPDecode.c
gcc -Wall -Wextra -Wno-unused-parameter -c IPEncode.c
gcc -Wall -Wextra -Wno-unused-parameter -c IPInAddr.c
gcc -Wall -Wextra -Wno-unused-parameter -c IPString.c
gcc -Wall -Wextra -Wno-unused-parameter -c MACAddr.c
gcc -Wall -Wextra -Wno-unused-parameter -c MACAddress.c
gcc -Wall -Wextra -Wno-unused-parameter -c MACDecode.c
gcc -Wall -Wextra -Wno-unused-parameter -c MACEncode.c
gcc -Wall -Wextra -Wno-unused-parameter -c MACSpec.c
# gcc -Wall -Wextra -Wno-unused-parameter -c OUIName.c
gcc -Wall -Wextra -Wno-unused-parameter -c fcs.c
gcc -Wall -Wextra -Wno-unused-parameter -c getIPv4.c
gcc -Wall -Wextra -Wno-unused-parameter -c isIPv4.c
gcc -Wall -Wextra -Wno-unused-parameter -c hostnics.c
# gcc -Wall -Wextra -Wno-unused-parameter -c anynic.c

# ====================================================================
#
# --------------------------------------------------------------------

gcc -Wall -Wextra -Wno-unused-parameter -c channel.c
gcc -Wall -Wextra -Wno-unused-parameter -c openchannel.c
gcc -Wall -Wextra -Wno-unused-parameter -c sendpacket.c
gcc -Wall -Wextra -Wno-unused-parameter -c readpacket.c
gcc -Wall -Wextra -Wno-unused-parameter -c closechannel.c
gcc -Wall -Wextra -Wno-unused-parameter -c gethwaddr.c
gcc -Wall -Wextra -Wno-unused-parameter -c getifname.c

# ====================================================================
#  
# --------------------------------------------------------------------

rm -f *.o

