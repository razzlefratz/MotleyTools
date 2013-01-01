/*====================================================================*
 *
 *   info.h - 
 *
 *.  Motley Tools by Charles Maier
 *:  modified tue 16 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef INFO_HEADER
#define INFO_HEADER

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#include "../date/date.h"
#include "../tools/sizes.h"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define PACKAGE_MAX 80
#define VERSION_MAX 80
#define CONTACT_MAX 80

/*====================================================================*
 *   data type declarations; 
 *--------------------------------------------------------------------*/

typedef struct _info_ 

{
	char thisyear [5];
	char thisdate [DATETIME_MAX];
	char hostname [HOSTNAME_MAX];
	char username [USERNAME_MAX];
	char released [PREAMBLE_MAX];
	char licensed [PREAMBLE_MAX];
	char packaged [PREAMBLE_MAX];
}

INFO;
void setinfo ();

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

