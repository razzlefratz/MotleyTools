/*====================================================================*
 *
 *   network.h - network related constants, structures, function and macros;
 * 
 *.  Motley Tools by Charles Maier
 *:  modified fri 20 feb 04 by user root on host zeus.cmassoc.net;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef NETWORK_HEADER
#define NETWORK_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define MAC_ADDR_SIZE 6
#define MAC_ADDR_LENGTH 12
#define MAC_ADDR_TOOSHORT -1
#define MAC_ADDR_TOOLONG  -2
#define MAC_ADDR_ILLEGAL  -3

#define IP_ADDR_OCTETS 4
#define IP_ADDR_MINLENGTH 7
#define IP_ADDR_MAXLENGTH 15
#define IP_ADDR_DOT '.'

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

int MACAddress (unsigned char address [], size_t octets, char const *string);
char const *IPString (unsigned address);
char const *IPDotted (unsigned address);
unsigned IPNumber (char const *address);
unsigned IPInAddr (char const *address);
bool isIPv4 (char const *string);
char *getIPv4 (char buffer [], size_t length, FILE *fp);

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

