/*====================================================================*
 *
 *   oglossary.cpp - implementation of the oglossary class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *
 *--------------------------------------------------------------------*/

#ifndef oGLOSSARY_SOURCE
#define oGLOSSARY_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oglossary.hpp"

/*====================================================================*
 *
 *   char const *oglossary::title() const;
 *
 *   return the instance title as a NUL terminated string;
 *
 *--------------------------------------------------------------------*/

char const * oglossary::title() const

{
	return (this->mlist->title());
}

/*====================================================================*
 *
 *   oglossary &oglossary::title(char const *string);
 *
 *   replace the instance title with the NUL terminated string argument;
 *
 *--------------------------------------------------------------------*/

oglossary & oglossary::title(char const * string)

{
	this->mlist->title(string);
	return (* this);
}

/*====================================================================*
 *
 *   size_t oglossary::index() const;
 *
 *
 *--------------------------------------------------------------------*/

size_t oglossary::index() const

{
	return (this->mlist->index());
}

/*====================================================================*
 *
 *   size_t oglossary::count() const;
 *
 *
 *--------------------------------------------------------------------*/

size_t oglossary::count() const

{
	return (this->mlist->count());
}

/*====================================================================*
 * 
 *   char const *oglossary::symbol();
 *
 *
 *--------------------------------------------------------------------*/

char const * oglossary::symbol() const

{
	oitem * item = this->mlist->item();
	return (item != (oitem *)(0)? item->name(): (char *)(0));
}

/*====================================================================*
 *
 *   char const *oglossary::string();
 *
 *
 *--------------------------------------------------------------------*/

char const * oglossary::string() const

{
	oitem * item = this->mlist->item();
	return (item != (oitem *)(0)? item->name(): (char *)(0));
}

/*====================================================================*
 *
 *   char const *oglossary::symbols(size_t index);
 *
 *
 *--------------------------------------------------------------------*/

char const * oglossary::symbols(size_t index) const

{
	oitem * item = this->mlist->items(index);
	return (item != (oitem *)(0)? item->name(): (char *)(0));
}

/*====================================================================*
 *
 *   char const *oglossary::strings(size_t index);
 *
 *
 *--------------------------------------------------------------------*/

char const * oglossary::strings(size_t index) const

{
	oitem * item = this->mlist->items(index);
	return (item != (oitem *)(0)? item->name(): (char *)(0));
}

/*====================================================================*
 *
 *   bool oglossary::defined(char const *symbol);
 *
 *
 *--------------------------------------------------------------------*/

bool oglossary::defined(char const * symbol)

{
	return (this->mlist->defined(symbol));
}

/*====================================================================*
 *
 *   size_t oglossary::indexof(char const *symbol);
 *
 *
 *--------------------------------------------------------------------*/

size_t oglossary::indexof(char const * symbol)

{
	return (this->mlist->indexof(symbol));
}

/*====================================================================*
 *
 *   char const *oglossary::lookup(char const *symbol);
 *
 *
 *--------------------------------------------------------------------*/

char const * oglossary::lookup(char const * symbol)

{
	oitem * item = this->mlist->item(symbol);
	return (item != (oitem *)(0)? item->text(): (char *)(0));
}

/*====================================================================*
 *
 *   char const *oglossary::expand(char const *symbol);
 *
 *
 *--------------------------------------------------------------------*/

char const * oglossary::expand(char const * symbol)

{
	oitem * item = this->mlist->item(symbol);
	return (item != (oitem *)(0)? item->text(): symbol);
}

/*====================================================================*
 *
 *   bool oglossary::create(char const *symbol, char const *string);
 *
 *
 *--------------------------------------------------------------------*/

bool oglossary::create(char const * symbol, char const * string)

{
	oitem * item = this->mlist->item(symbol);
	if (item == (oitem *)(0))
	{
		item = new oitem(symbol, string);
		this->mlist->insertitem(item);
		return (true);
	}
	else 
	{
		return (false);
	}
}

/*====================================================================*
 *
 *   bool oglossary::define(char const *symbol, char const *string);
 *
 *
 *--------------------------------------------------------------------*/

bool oglossary::define(char const * symbol, char const * string)

{
	oitem * item = this->mlist->item(symbol);
	if (item == (oitem *)(0))
	{
		item = new oitem(symbol, string);
		this->mlist->insertitem(item);
		return (true);
	}
	else 
	{
		item->text(string);
		return (false);
	}
}

/*====================================================================*
 *
 *   bool oglossary::assign(char const *symbol, char const *string);
 *
 *
 *--------------------------------------------------------------------*/

bool oglossary::assign(char const * symbol, char const * string)

{
	oitem * item = this->mlist->item(symbol);
	if (item != (oitem *)(0))
	{
		item->text(string);
		return (true);
	}
	else 
	{
		return (false);
	}
}

/*====================================================================*
 *
 *   oglossary & oglossary::clear();
 *
 *
 *--------------------------------------------------------------------*/

oglossary & oglossary::clear()

{
	this->mlist->clear();
	return (* this);
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

oglossary::oglossary(signed order(char const *, char const *))

{
	this->mlist = new olist(order);
	return;
}

oglossary::oglossary()

{
	this->mlist = new olist;
	return;
}

oglossary::~ oglossary()

{
	delete this->mlist;
	return;
}

/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif



