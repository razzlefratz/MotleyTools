/*====================================================================*
 *
 *   int scansize (SCAN *scan, LOGSET *logset);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANSIZE_SOURCE
#define SCANSIZE_SOURCE

#include <ctype.h>
#include <errno.h>

#include "../recycle/recycle.h"
#include "../tools/error.h"

int scansize (SCAN *scan, LOGSET *logset) 

{
	while (isblank (*scan->cp)) 
	{
		++scan->cp;
	}
	logset->threshold = 0;
	for (scan->tp = scan->token; isdigit (*scan->cp); *scan->tp++ = *scan->cp++) 
	{
		logset->threshold *= 10;
		logset->threshold += *scan->cp - '0';
	}
	switch (*scan->cp) 
	{
	case 'G':
	case 'g':
		logset->threshold *= 1024;
	case 'M':
	case 'm':
		logset->threshold *= 1024;
	case 'K':
	case 'k':
		logset->threshold *= 1024;
		*scan->tp++ = *scan->cp++;
		break;
	default:
		break;
	}
	*scan->tp = (char) (0);
	if (!isblank (*scan->cp) && !isbreak (*scan->cp)) 
	{
		error_on_line (0, EINVAL, scan->file, scan->line, "threshold '%s' has unexpected terminatoR", scan->token);
		return (1);
	}
	return (0);
}


#endif

