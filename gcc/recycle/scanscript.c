/*====================================================================*
 *
 *   static char *scanscript (SCAN *scan);
 *   
 *   scan entire scriptBody (newlines and all) and return it as a
 *   new string; 
 *   
 *   this function assumes the 'prerecycle. or 'postrecycle. options
 *   and trailing blanks have been scanned by the caller; the next
 *   character should be some break character; 
 * 
 *   this function scans entire lines up to but excluding the next
 *   "endscript" option line; the script includes the newline that
 *   precedes; 
 *
 *   sp means (s)tart (p)ointer and ep means (e)nd (p)ointer; don't
 *   confuse them with scan->sp or scan->cp; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SCANSCRIPT_SOURCE
#define SCANSCRIPT_SOURCE

#include <ctype.h>
#include <string.h>

#include "../recycle/recycle.h"
#include "../tools/memory.h"
#include "../tools/tools.h"

char *scanscript (SCAN *scan) 

{
	char *scriptBody;
	char *sp;
	char *ep;
	for (sp = ep = ++scan->cp; *scan->cp != (char) (0); ep = ++scan->cp) 
	{
		while (isblank (*scan->cp)) 
		{
			++scan->cp;
		}
		for (scan->sp = scan->token; isalpha (*scan->cp); *scan->sp++ = *scan->cp++);
		*scan->sp = (char) (0);
		if (!strcmp (scan->token, "endscript")) 
		{
			break;
		}
		while (!newline (*scan->cp)) 
		{
			++scan->cp;
		}
		++scan->line;
	}
	scriptBody = (char *)(emalloc ((ep - sp) + 1));
	strncpy (scriptBody, sp, ep - sp);
	scriptBody [ep - sp] = (char) (0);
	return (scriptBody);
}


#endif

