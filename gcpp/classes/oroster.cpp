/*====================================================================*
 *
 *   oroster.cpp - implementation of the oroster class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oROSTER_SOURCE
#define oROSTER_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oroster.hpp"

/*====================================================================*
 *
 *   char const *title() const;
 *
 *
 *--------------------------------------------------------------------*/

char const * oroster::title () const 

{
	return (this->mlist->title ());
}

/*====================================================================*
 *
 *   oroster & title(char const *title);
 *
 *
 *--------------------------------------------------------------------*/

oroster & oroster::title (char const * title) 

{
	this->mlist->title (title);
	return (* this);
}

/*====================================================================*
 *
 *   unsigned index() const;
 *
 *
 *--------------------------------------------------------------------*/

unsigned oroster::index () const 

{
	return (this->mlist->index ());
}

/*====================================================================*
 *
 *   unsigned count() const;
 *
 *
 *--------------------------------------------------------------------*/

unsigned oroster::count () const 

{
	return (this->mlist->count ());
}

/*====================================================================*
 *
 *   char const * operator[](signed index);
 *
 *
 *--------------------------------------------------------------------*/

char const * oroster::operator [] (signed index) const 

{
	oitem * item = this->mlist->cycle (index);
	return (item != (oitem *) (0)? item->name (): (char *) (0));
}

/*====================================================================*
 *
 *   bool operator += (char const *symbol);
 *
 *
 *--------------------------------------------------------------------*/

bool oroster::operator += (char const * symbol) 

{
	return (this->insert (symbol));
}

/*====================================================================*
 *
 *   bool operator -= (char const *symbol);
 *
 *
 *--------------------------------------------------------------------*/

bool oroster::operator -= (char const * symbol) 

{
	return (this->remove (symbol));
}

/*====================================================================*
 *
 *   char const *symbol();
 *
 *
 *--------------------------------------------------------------------*/

char const * oroster::symbol () const 

{
	oitem * item = this->mlist->item ();
	return (item != (oitem *) (0)? item->name (): (char *) (0));
}

/*====================================================================*
 *
 *   char const *symbols(size_t index);
 *
 *
 *--------------------------------------------------------------------*/

char const * oroster::symbols (size_t index) const 

{
	oitem * item = this->mlist->items (index);
	return (item != (oitem *) (0)? item->name (): (char *) (0));
}

/*====================================================================*
 *
 *   bool defined(char const *symbol);
 *
 *
 *--------------------------------------------------------------------*/

bool oroster::defined (char const * symbol) 

{
	return (this->mlist->defined (symbol));
}

/*====================================================================*
 *
 *   unsigned indexof(char const *symbol);
 *
 *
 *--------------------------------------------------------------------*/

unsigned oroster::indexof (char const * symbol) 

{
	return (this->mlist->indexof (symbol));
}

/*====================================================================*
 *
 *   bool insert(char const *symbol);
 *
 *
 *--------------------------------------------------------------------*/

bool oroster::insert (char const * symbol) 

{
	oitem * item = this->mlist->item (symbol);
	if (item == (oitem *) (0)) 
	{
		item = new oitem (symbol);
		this->mlist->insertitem (item);
		return (true);
	}
	else 
	{
		return (false);
	}
}

/*====================================================================*
 *
 *   bool remove(char const *symbol);
 *
 *
 *--------------------------------------------------------------------*/

bool oroster::remove (char const * symbol) 

{
	oitem * item = this->mlist->item (symbol);
	if (item != (oitem *) (0)) 
	{
		this->mlist->removeitem ();
		return (true);
	}
	else 
	{
		return (false);
	}
}

/*====================================================================*
 *
 *   oroster & clear();
 *
 *
 *--------------------------------------------------------------------*/

oroster & oroster::clear () 

{
	this->mlist->clear ();
	return (* this);
}

/*====================================================================*
 *
 *   oroster (signed order (char const *, char const *));
 *   
 *   
 *--------------------------------------------------------------------*/

oroster::oroster (signed order (char const *, char const *)) 

{
	this->mlist = new olist (order);
	return;
}

/*====================================================================*
 *
 *   oroster ();
 *   
 *   
 *--------------------------------------------------------------------*/

oroster::oroster () 

{
	this->mlist = new olist;
	return;
}

/*====================================================================*
 *
 *   ~oroster ();
 *   
 *   
 *--------------------------------------------------------------------*/

oroster::~oroster () 

{
	delete this->mlist;
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

