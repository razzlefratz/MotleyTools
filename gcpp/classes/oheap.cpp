/*====================================================================*
 *
 *   oheap.cpp - implementation of the oheap class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oHEAP_SOURCE
#define oHEAP_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oheap.hpp"
#include "../../gcc/tools/sizes.h"

/*====================================================================*
 *
 *   char const *oheap::title() const;
 *
 *   return instance title as a constant string;
 *
 *--------------------------------------------------------------------*/

char const * oheap::title() const

{
	return (this->mtitle);
}

/*====================================================================*
 *
 *   oheap &oheap::title(char const *string)
 *
 *   replace the instance title with the string argument if they differ;
 *
 *--------------------------------------------------------------------*/

oheap & oheap::title(char const * string)

{
	if (std::strcmp(string, this->mtitle))
	{
		delete [] this->mtitle;
		this->mtitle = new char[strlen(string) +  1];
		strcpy (this->mtitle, string);
	}
	return (* this);
}

/*====================================================================*
 *
 *   size_t oheap::count() const;
 *
 *
 *--------------------------------------------------------------------*/

size_t oheap::count() const

{
	return (this->mcount);
}

/*====================================================================*
 *
 *   oitem * oheap::item() const;
 *
 *
 *--------------------------------------------------------------------*/

oitem * oheap::item() const

{
	return (this->mcount > 0? this->mtable[this->mstart]: (oitem *)(0));
}

/*====================================================================*
 *
 *   oitem * oheap::fetch();
 *
 *
 *--------------------------------------------------------------------*/

oitem * oheap::item()

{
	if (this->mcount < this->mstart)
	{
		return ((oitem *)(0));
	}
	if (this->mcount > this->mlimit)
	{
		return ((oitem *)(0));
	}

/*
 * Do not use table[0] because this algorithm depends on the
 * oheap root being a positive odd integer, specifically 1.
 *
 * I have taken a liberty with this algorithm. Normally one 
 * does a list[start] = list[count--] and temp = list[start];
 * Instead we use list[count] as temp which alters the bound
 * testing because count is now 1 greater than normal. Check 
 * this against the book if in doubt.
 */

	oitem * item = this->mtable[this->mstart];
	this->mlower = this->mstart;
	while ((this->mupper = (this->mlower << 1)) < this->mcount)
	{
		if ((* this->morder)(this->mtable[this->mupper] ->name(), this->mtable[this->mupper +  1] ->name()) > 0)
		{
			this->mupper++;
		}
		if ((* this->morder)(this->mtable[this->mcount] ->name(), this->mtable[this->mupper +  0] ->name()) <= 0)
		{
			break;
		}
		this->mtable[this->mlower] = this->mtable[this->mupper];
		this->mlower = this->mupper;
	}
	this->mtable[this->mlower] = this->mtable[this->mcount];
	this->mtable[this->mcount--] = (oitem *)(0);
	return (item);
}

/*====================================================================*
 *
 *   oheap & oheap::insertitem(oitem *item)
 *
 *
 *--------------------------------------------------------------------*/

oheap & oheap::insertitem(oitem * item)

{
	if (++ mcount > mlimit)
	{
		oitem ** table = this->mtable;
		this->mlimit = this->mlimit +  this->mblock;
		this->mblock = this->mlimit - this->mblock;
		this->mtable = new oitem * [this->mlimit];
		for (size_t index = 0; index < this->mlimit; ++ index)
		{
			this->mtable[index] = table[index];
		}
		delete [] table;
	}
	this->mupper = this->mcount;
	while (this->mupper > this->mstart)
	{
		this->mlower = this->mupper >> 1;
		if ((* this->morder)(item->name(), this->mtable[this->mlower] ->name()) >= 0)
		{
			break;
		}
		this->mtable[this->mupper] = this->mtable[this->mlower];
		this->mupper = this->mlower;
	}
	this->mtable[this->mupper] = item;
	return (* this);
}

/*====================================================================*
 *
 *   oheap & oheap::clear();
 *
 *
 *--------------------------------------------------------------------*/

oheap & oheap::clear()

{
	while (mcount > 0)
	{
		delete this->mtable[this->mcount--];
	}
	return (* this);
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

oheap::oheap()

{
	this->mtitle = new char[1];
	this->mtitle[0] = (char)(0);
	this->mtable = new oitem * [_LISTSIZE];
	this->mlimit = _LISTSIZE;
	this->mblock = _LISTSIZE;
	this->mstart = 1;
	this->mcount = 0;
	this->morder = std::strcmp;
	return;
}

oheap::oheap(int order(char const *, char const *))

{
	this->mtitle = new char[1];
	this->mtitle[0] = (char)(0);
	this->mtable = new oitem * [_LISTSIZE];
	this->mlimit = _LISTSIZE;
	this->mblock = _LISTSIZE;
	this->mstart = 1;
	this->mcount = 0;
	this->morder = order;
	return;
}

oheap::~ oheap()

{
	delete [] this->mtitle;
	delete [] this->mtable;
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif



