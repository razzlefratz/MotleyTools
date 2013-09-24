/*====================================================================*
 *
 *   tabs.c - tabcolumn set/clear functions
 *
 *   tools/tabs.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>

/*====================================================================*
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *--------------------------------------------------------------------*/

#include <stdlib.h>

#include "../tools/tools.h"
#include "../tools/memory.h"
#include "../tools/tabs.h"

/*====================================================================*
 *   local definitions and declarations;
 *--------------------------------------------------------------------*/

static signed * ruler = NULL;
static size_t limit = TABS_L_RULER;

/*====================================================================*
 *
 *   bool tabset(int set, const int tab);
 *
 *   tabs.h
 *
 *   This function records tab settings in the tabstop ruler. If a ruler
 *   has not yet been created, using tabend(), then one is created. Once
 *   setting are recorded, tabcol() May be used to lookup them up, later.
 *
 *   A tab is first set in one column and then replicated (at intervals)
 *   to the right, along the ruler and intervening tabstops are cleared.
 *   The replication interval May negative, zero or positive. A negative
 *   or zero value suppresses replication. A negative value prevents the
 *   clearing of previously set tabs. Here are some examples:
 *
 *   tabset(0,0)   - clears all tabstops within the scope of the ruler.
 *
 *   tabset(0,1)   - sets tabstops in every column of the ruler.
 *
 *   tabset(1,8)   - sets a tabstop in column 1 and every eight columns
 *                   there after; any previously set tabs, after column
 *                   1 are cleared.
 *
 *   tabset(16,0)  - sets a tabstop in column 16, clearing those after.
 *
 *   tabset(16,-1) - sets a tabstop in column 16, leaving others set.
 *
 *   A tabstop is set by inserting logical true in the ruler[] at the
 *   location corresponding to the desired column.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool tabset(size_t set, int tab)

{
	size_t col = 0;
	if (ruler == NULL)
	{
		ruler = (signed *) (emalloc(limit * sizeof(signed)));
		tabset (0, 0);
	}
	if (tab >= 0)
	{
		for (col = set; col < limit; col++)
		{
			if (col == set)
			{
				ruler [col] = true;
				set += tab;
			}
			else 
			{
				ruler [col] = false;
			}
		}
	}
	else 
	{
		ruler [set] = true;
	}
	return ((tab > 0)? (set - tab): (set));
}

/*====================================================================*
 *
 *   bool tabcol(size_t column);
 *
 *   tabs.h
 *
 *   This function returns logical true if a tabstop has been set in the
 *   specified column on the ruler. By default, tabstops are set in all
 *   columns to the left and to the right of the ruler. If the ruler has
 *   not been defined then tabstops default to every 8 columns starting
 *   with column 0.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool tabcol(size_t col)

{
	if (ruler)
	{
		return ((col < limit)? (ruler[col]): true);
	}
	else 
	{
		return (col % TABS_O_SPACE == 0);
	}
}

/*====================================================================*
 *
 *   void tabend(size_t column);
 *
 *   tabs.h
 *
 *   Set the maximum size of the tabstop ruler. There are no limits on the
 *   the size if called before the first call to tabset(); after that, the
 *   value can't exceed the limit.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

size_t tabend(size_t col)

{
	if ((! ruler) || (col < limit)) limit = col;
	return (limit);
}

