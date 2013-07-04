/*====================================================================*
 *
 *   tabrule.cpp - implementation of the tabrule class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oTABRULE_SOURCE
#define oTABRULE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/otabrule.hpp"

/*====================================================================*
 *
 *   tabrule & tabrule::clear ();
 *
 *
 *--------------------------------------------------------------------*/

tabrule & tabrule::clear () 

{
	for (mcolumn = 0; mcolumn < mmargin; ++mcolumn) 
	{
		mruler [mcolumn] = false;
	}
	return (* this);
}

/*====================================================================*
 *
 *   tabrule & tabrule::reset ();
 *
 *
 *--------------------------------------------------------------------*/

tabrule & tabrule::reset () 

{
	for (mcolumn = 0; mcolumn < mmargin; ++mcolumn) 
	{
		mruler [mcolumn] = mcolumn % mindent? false: true;
	}
	return (* this);
}

/*====================================================================*
 *
 *   unsigned tabrule::margin () const;
 *
 *
 *--------------------------------------------------------------------*/

unsigned tabrule::margin () const 

{
	return (mmargin);
}

/*====================================================================*
 *
 *   unsigned tabrule::indent () const;
 *
 *
 *--------------------------------------------------------------------*/

unsigned tabrule::indent () const 

{
	return (mindent);
}

/*====================================================================*
 *
 *   bool tabrule::tabcol (unsigned column) ;
 *
 *   Return true it the specfied column is a tab column. All columns
 *   after the margin are tab columns.
 *
 *--------------------------------------------------------------------*/

bool tabrule::tabcol (unsigned column) 

{
	return ((column < mmargin)? (mruler [column]): true);
}

/*====================================================================*
 *
 *   tabrule & tabrule::tabset (unsigned column, signed indent);
 *
 *   Record tab settings in the ruler.
 *
 *   A tab is set in column and replicated at intervals. Intervening
 *   tabs are cleared for positive intervals. All following tabs are
 *   cleared for interval 0. None are cleared for negative intervals.
 *
 *   tabset(0,0)   - clears all tabs to the margin.
 *
 *   tabset(0,1)   - set tabs in every column.
 *
 *   tabset(1,8)   - sets a tab in column 1 and every eight columns
 *                   there after; previously set tabs, after column
 *                   1 are cleared.
 *
 *   tabset(16,0)  - sets a tab in column 16 and clears those after.
 *
 *   tabset(16,-1) - sets a tab in column 16 and leaves others set.
 *
 *--------------------------------------------------------------------*/

tabrule & tabrule::tabset (unsigned column, signed indent) 

{
	if (indent >= 0) 
	{
		for (mcolumn = column; mcolumn < mmargin; mcolumn++) 
		{
			if (mcolumn == column) 
			{
				mruler [mcolumn] = true;
				column += indent;
			}
			else
			{
				mruler [mcolumn] = false;
			}
		}
	}
	else if (column < mmargin) 
	{
		mruler [column] = true;
	}
	return (* this);
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

tabrule::tabrule (unsigned margin, signed indent) 

{
	mmargin = margin;
	mindent = indent;
	mruler = new bool [mmargin];
	for (mcolumn = 0; mcolumn < mmargin; ++mcolumn) 
	{
		mruler [mcolumn] = mcolumn % mindent? false: true;
	}
};

tabrule::tabrule () 

{
	mmargin = 0xFF;
	mindent = 0x08;
	mruler = new bool [mmargin];
};

tabrule::~tabrule () 

{
	delete [] mruler;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

