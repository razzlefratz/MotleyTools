/*====================================================================*
 *
 *   sv_fattr - File Attribute String Vector
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STDDEF_INCLUDE
#include <stddef.h>
#endif

#define SV_FATTR 7

char *sv_fattr [SV_FATTR+1] = 

{
	"R/O",
	"HID",
	"SYS",
	"VOL",
	"DIR",
	"ARC",
	"NIL",
	NULL
};

