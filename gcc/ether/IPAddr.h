/*====================================================================*
 *
 *   IPAddr.h - IP Address encode and decode functions; 
 * 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef IPADDR_HEADER
#define IPADDR_HEADER

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

#define IP_ADDR_OCTETS 4
#define IP_ADDR_MINLENGTH 7
#define IP_ADDR_MAXLENGTH 15
#define IP_ADDR_EXTENDER '.'

#define IP_ADDR_ILLEGAL  -1
#define IP_ADDR_TOOSHORT -2
#define IP_ADDR_TOOLONG  -3

/*====================================================================*
 *   data types;
 *--------------------------------------------------------------------*/

typedef union 

{
	unsigned value;
	unsigned char octet [IP_ADDR_OCTETS];
}

IPA;

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

char const *IPString (unsigned address);
char const *IPDecode (unsigned address);
unsigned IPEncode (char const *address);
unsigned IPInAddr (char const *address);
bool isIPv4 (char const *string);
char *getIPv4 (char buffer [], size_t length, FILE *fp);

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

