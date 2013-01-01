/*====================================================================*
 *
 *  void cgipeek (char const * vector []);
 *
 *   cgi.h
 *
 *   print a string vector on stdout in HTML format; the vector is
 *   assumed to contain label/value pairs delimited by an equal as
 *   done in the environment vector;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CGIPEEK_SOURCE
#define CGIPEEK_SOURCE

#include <stdio.h>
#include <memory.h>

#include "../html/cgi.h"
#include "../tools/tools.h"

void cgipeek (char const * vector []) 

{
	if (vector) 
	{
		char symbol [256];
		signed margin = 0;
		indent (margin++, "<div class='peek'>");
		indent (margin++, "<style type='text/css'>");
		indent (margin, "th.peek { background:lime;text-align:left;font:normal 10pt monospace;width: 25%%; }");
		indent (margin, "td.peek { background:aqua;text-align:left;font:normal 10pt monospace;width: 75%%; }");
		indent (margin--, "</style>");
		indent (margin++, "<table style='width:100%%'>");
		while (*vector) 
		{
			char const * string = * vector;
			memset (symbol, 0, sizeof (symbol));
			while (*string) 
			{
				if (*string++ == '=') 
				{
					memcpy (symbol, *vector, string - *vector - 1);
					break;
				}
			}
			indent (margin++, "<tr>");
			indent (margin++, "<th class='peek'>");
			indent (margin, "%s", symbol);
			indent (margin--, "</th>");
			indent (margin++, "<td class='peek'>");
			indent (margin, "%s", string);
			indent (margin--, "</td>");
			indent (margin--, "</tr>");
			vector++;
		}
		indent (margin--, "</table>");
		indent (margin--, "</div>");
	}
	return;
}


#endif

