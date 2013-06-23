/*====================================================================*
 *
 *   ocatalog.cpp - implementation of the ocatalog class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCATALOG_SOURCE
#define oCATALOG_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ocatalog.hpp"

/*====================================================================*
 *
 *   char const * title() const;
 *
 *   return the object title as a conventional string;
 *
 *--------------------------------------------------------------------*/

char const * ocatalog::title () const 

{
	return (this->mlist->title ());
}

/*====================================================================*
 *
 *   ocatalog & title(char const *string);
 *
 *   replace the object title the conventional string argument;
 *
 *--------------------------------------------------------------------*/

ocatalog & ocatalog::title (char const * string) 

{
	this->mlist->title (string);
	return (* this);
}

/*====================================================================*
 *
 *   char const * symbol();
 *
 *
 *--------------------------------------------------------------------*/

char const * ocatalog::symbol () 

{
	oitem * item = this->mlist->item ();
	return (item != (oitem *) (0)? item->name (): (char *) (0));
}

/*====================================================================*
 *
 *   char const * string();
 *
 *
 *--------------------------------------------------------------------*/

char const * ocatalog::string () 

{
	oitem * item = this->mlist->item ();
	return (item != (oitem *) (0)? item->text (): (char *) (0));
}

/*====================================================================*
 *
 *   char const * symbols(unsigned index);
 *
 *
 *--------------------------------------------------------------------*/

char const * ocatalog::symbols (unsigned index) 

{
	oitem * item = this->mlist->items (index);
	return (item != (oitem *) (0)? item->name (): (char *) (0));
}

/*====================================================================*
 *
 *   char const * strings(unsigned index);
 *
 *
 *--------------------------------------------------------------------*/

char const * ocatalog::strings (unsigned index) 

{
	oitem * item = this->mlist->items (index);
	return (item != (oitem *)(0)? item->text (): (char *) (0));
}

/*====================================================================*
 *
 *   bool related(char const *symbol, char const *string);
 *
 *
 *--------------------------------------------------------------------*/

bool ocatalog::related (char const * symbol, char const * string) 

{
	return (this->mlist->defined (symbol, string));
}

/*====================================================================*
 *
 *   unsigned indexof(char const *symbol, char const *string);
 *
 *
 *--------------------------------------------------------------------*/

unsigned ocatalog::indexof (char const * symbol, char const * string) 

{
	return (this->mlist->indexof (symbol, string));
}

/*====================================================================*
 *
 *   bool relate(char const *major, char const *minor);
 *
 *
 *--------------------------------------------------------------------*/

bool ocatalog::relate (char const * major, char const * minor) 

{
	oitem * item = this->mlist->item (major, minor);
	if (item == (oitem *) (0)) 
	{
		item = new oitem (major, minor);
		this->mlist->insertitem (item);
		return (true);
	}
	return (false);
}

/*====================================================================*
 *
 *   ocatalog & clear();
 *
 *
 *--------------------------------------------------------------------*/

ocatalog & ocatalog::clear () 

{
	this->mlist->clear ();
	return (* this);
}

/*====================================================================*
 * 
 *   ocatalog (signed order (char const *, char const *));
 *   
 *   
 *--------------------------------------------------------------------*/

ocatalog::ocatalog (signed order (char const *, char const *)) 

{
	this->mlist = new olist (order);
	return;
}

/*====================================================================*
 * 
 *   ocatalog ();
 *   
 *   
 *--------------------------------------------------------------------*/

ocatalog::ocatalog () 

{
	this->mlist = new olist;
	return;
}

/*====================================================================*
 *   
 *   ~ocatalog ();
 *   
 *   
 *--------------------------------------------------------------------*/

ocatalog::~ocatalog () 

{
	delete this->mlist;
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

