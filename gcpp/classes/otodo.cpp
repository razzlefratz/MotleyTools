/*====================================================================*
 *
 *   otodo.cpp - implementation of the otodo class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oTODO_SOURCE
#define oTODO_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "tools.h"
#include "../classes/otodo.hpp"

/*====================================================================*
 *
 *   char const *otodo::title() const;
 *
 *   return the instance title as a NUL terminated string;
 *
 *--------------------------------------------------------------------*/

char const *otodo::title () const 

{
	return (this->mtitle);
}


/*====================================================================*
 *
 *   otodo &otodo::title(char const *string)
 *
 *   replace the instance title with the NUL terminated string argument;
 *
 *--------------------------------------------------------------------*/

otodo & otodo::title (char const *string) 

{
	delete [] this->mtitle;
	this->mtitle = new char [std::strlen (string) + 1];
	std::strcpy (this->mtitle, string);
	return (*this);
}


/*====================================================================*
 *
 *   size_t otodo::index() const;
 *
 *   return the current list index; the list index is read only and may
 *   change after each list operation; 
 *
 *--------------------------------------------------------------------*/

size_t otodo::index () const 

{
	return (this->mindex);
}


/*====================================================================*
 *
 *   size_t otodo::start() const;
 *
 *   the index of the first list item; this value is normally 0 and does
 *   not change; the value might change if the object is redesigned;
 *
 *--------------------------------------------------------------------*/

size_t otodo::start () const 

{
	return (this->mstart);
}


/*====================================================================*
 *
 *   size_t otodo::count() const;
 *
 *   returns the number of items in the list; 
 *
 *--------------------------------------------------------------------*/

size_t otodo::count () const 

{
	return (this->mcount);
}


/*====================================================================*
 *
 *   size_t otodo::block() const;
 *
 *   the number of elements that will be added to the list when it next
 *   expands; 
 *
 *   this value increases after each expansion in a fibanocci progression;
 *
 *--------------------------------------------------------------------*/

size_t otodo::block () const 

{
	return (this->mblock);
}


/*====================================================================*
 *
 *   size_t otodo::limit() const;
 *
 *   the number of elements current available in the list; the list will
 *   automatically expand if the count exceeds the limit; 
 *
 *   this value increases after each expansion in a fibanocci progression;
 *
 *--------------------------------------------------------------------*/

size_t otodo::limit () const 

{
	return (this->mlimit);
}


/*====================================================================*
 *
 *   oitem *otodo::item() const
 *
 *   return the item stored at the current table position; return nothing
 *   for invalid table positions;
 *
 *--------------------------------------------------------------------*/

oitem *otodo::item () const 

{
	return (this->mindex < this->mcount? this->mtable [this->mindex]: (oitem *) (0));
}


/*====================================================================*
 *
 *   oitem *otodo::items(size_t index) const;
 *
 *   return the object stored at the specified table position; return a 
 *   null object pointer for invalid table positions;
 *
 *--------------------------------------------------------------------*/

oitem *otodo::items (size_t index) const 

{
	return (index < this->mcount? this->mtable [index]: (oitem *) (0));
}


/*====================================================================*
 *
 *   bool otodo::defined(char const *string);
 *
 *   return true if the list contains an object having the same name as
 *   as the string argument; 
 *
 *--------------------------------------------------------------------*/

bool otodo::defined (char const *string) 

{
	return (this->indexof (string) < this->mcount);
}


/*====================================================================*
 *
 *   size_t otodo::indexof(char const *string);
 *
 *   return the index if the first object having the same name as the 
 *   string argument; return a value from mstart to mcount where mcount 
 *   means no such object found;
 *
 *--------------------------------------------------------------------*/

size_t otodo::indexof (char const *string) 

{
	return (this->select (string).index ());
}


/*====================================================================*
 *
 *   size_t otodo::select(char const *string);
 *
 *   return the index if the first object having the same name as the 
 *   string argument; return a value from mstart to mcount where mcount 
 *   means no such object found;
 *
 *--------------------------------------------------------------------*/

otodo & otodo::select (char const *string) 

{
	for (this->mindex = this->mstart; this->mindex < this->mcount; this->mindex++) 
	{
		if (std::strcmp (string, this->mtable [this->mindex] ->name ()) == 0) 
		{
			break;
		}
	}
	return (*this);
}


/*====================================================================*
 *
 *   oitem *otodo::item(char const *symbol) 
 *
 *
 *--------------------------------------------------------------------*/

oitem *otodo::item (char const *symbol) 

{
	return (this->select (symbol).item ());
}


/*====================================================================*
 *
 *   otodo &otodo::insertitem(oitem *item);
 *
 *   append the object argument to mtable[]; expand mtable[] if needed to
 *   accomodate the object;
 *
 *--------------------------------------------------------------------*/

otodo & otodo::insertitem (oitem *item) 

{
	if (this->mcount >= this->mlimit) 
	{
		oitem **otable = this->mtable;
		this->mtable = new oitem *[this->mlimit + this->mblock];
		for (this->mindex = this->mstart; this->mindex < this->mlimit; this->mindex++) 
		{
			this->mtable [this->mindex] = otable [this->mindex];
		}
		this->mlimit = this->mlimit + this->mblock;
		this->mblock = this->mlimit - this->mblock;
		delete [] otable;
	}
	this->mtable [this->mcount++] = item;
	return (*this);
}


/*====================================================================*
 *
 *   otodo &otodo::appenditem(oitem *item);
 *
 *   append the object argument to mtable[]; expand mtable[] if needed to
 *   accomodate the object;
 *
 *--------------------------------------------------------------------*/

otodo & otodo::appenditem (oitem *item) 

{
	if (this->mcount >= this->mlimit) 
	{
		oitem **otable = this->mtable;
		this->mtable = new oitem *[this->mlimit + this->mblock];
		for (this->mindex = this->mstart; this->mindex < this->mlimit; this->mindex++) 
		{
			this->mtable [this->mindex] = otable [this->mindex];
		}
		this->mlimit = this->mlimit + this->mblock;
		this->mblock = this->mlimit - this->mblock;
		delete [] otable;
	}
	this->mtable [this->mcount++] = item;
	return (*this);
}


/*====================================================================*
 *
 *   otodo &otodo::removeitem(oitem *item);
 *
 *   remove the last item in mtable[]; return the object address; 
 *
 *--------------------------------------------------------------------*/

otodo & otodo::removeitem () 

{
	if (this->mcount > this->mstart) 
	{
		delete this->mtable [--this->mcount];
		this->mtable [this->mcount] = (oitem *) (0);
	}
	return (*this);
}


/*====================================================================*
 *
 *   otodo & otodo::orderlist();
 *
 *   sort mtable[] using a bridge sort;
 *
 *--------------------------------------------------------------------*/

otodo & otodo::orderlist () 

{
	for (this->mindex = this->mstart; this->mindex < this->mcount; this->mindex++) 
	{
		size_t index = this->mindex;
		oitem *entry = this->mtable [index];
		while ((index > this->mstart) && std::strcmp (entry->name (), this->mtable [index-1] ->name ()) > 0) 
		{
			this->mtable [index] = this->mtable [index-1];
			index--;
		}
		this->mtable [index] = entry;
	}
	return (*this);
}


/*====================================================================*
 *
 *   otodo & otodo::clearlist();
 *
 *
 *--------------------------------------------------------------------*/

otodo & otodo::clearlist () 

{
	delete [] this->mtable;
	this->mtable = new oitem *[this->mlimit];
	this->mstart = 0;
	this->mindex = 0;
	this->mcount = 0;
	return (*this);
}


/*====================================================================*
 *
 *   otodo::otodo();
 *
 *
 *--------------------------------------------------------------------*/

otodo::otodo () 

{
	this->mtitle = new char [1];
	this->mtitle [0] = (char) (0);
	this->mtable = new oitem *[_LISTSIZE];
	this->mblock = _LISTSIZE;
	this->mlimit = _LISTSIZE;
	this->mstart = 0;
	this->mindex = 0;
	this->mcount = 0;
	return;
}


/*====================================================================*
 *
 *   otodo::~otodo();
 *
 *
 *--------------------------------------------------------------------*/

otodo::~otodo () 

{
	delete [] this->mtitle;
	delete [] this->mtable;
	return;
}


/*====================================================================*
 * end implementation;
 *--------------------------------------------------------------------*/

#endif

