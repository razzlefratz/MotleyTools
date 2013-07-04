/*====================================================================*
 *
 *   olist.cpp - implementation of the olist class.
 *
 *   this object imlements an ordered list engine for oitem objects; it 
 *   is used by oroster, ocatalog and oglossary object classes to store,
 *   select and fetch information; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oLIST_SOURCE
#define oLIST_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/olist.hpp"
#include "../../gcc/tools/sizes.h"

/*====================================================================*
 *
 *   char const * title () const;
 *
 *   return the instance title as a costant string;
 *
 *--------------------------------------------------------------------*/

char const * olist::title () const 

{
	return (this->mtitle);
}

/*====================================================================*
 *
 *   olist & title (char const * title)
 *
 *   replace the instance title with the string argument if they differ;
 *
 *--------------------------------------------------------------------*/

olist & olist::title (char const * title) 

{
	if (std::strcmp (title, this->mtitle)) 
	{
		delete [] this->mtitle;
		this->mtitle = new char [strlen (title) + 1];
		strcpy (this->mtitle, title);
	}
	return (* this);
}

/*====================================================================*
 *
 *   unsigned count () const;
 *
 *   returns the number of items in the list; 
 *
 *--------------------------------------------------------------------*/

unsigned olist::count () const 

{
	return (this->mcount);
}

/*====================================================================*
 *
 *   unsigned index() const;
 *   unsigned lower() const;
 *   unsigned upper() const;
 *
 *   return the current list index; the list index may range from mstart
 *   to mcount and will change with each list object operation;
 *
 *--------------------------------------------------------------------*/

unsigned olist::index () const 

{
	return (this->mindex);
}

unsigned olist::lower () const 

{
	return (this->mlower);
}

unsigned olist::upper () const 

{
	return (this->mupper);
}

/*====================================================================*
 *
 *   oitem * item () const;
 *
 *   return the oitem pointer stored at the current list position; 
 *   return a void pointer if the current list position is mcount; 
 *
 *--------------------------------------------------------------------*/

oitem * olist::item () const 

{
	return (this->mindex < this->mcount? this->mtable [this->mindex]: (oitem *) (0));
}

/*====================================================================*
 *
 *   oitem * items (unsigned index) const;
 *
 *   return the oitem pointer stored at the specified list position; 
 *   return a void pointer if the specified list position is mcount;
 *
 *--------------------------------------------------------------------*/

oitem * olist::items (unsigned index) const 

{
	return (index < this->mcount? this->mtable [index]: (oitem *) (0));
}

/*====================================================================*
 *
 *   oitem * cycle (signed index) const;
 *
 *   return the oitem pointer stored at a relative list position; 
 *   return a void pointer if the list is empty;
 *
 *--------------------------------------------------------------------*/

oitem * olist::cycle (signed index) const 

{
	if (this->mcount > 0) 
	{
		index %= (signed) (this->mcount);
		index += this->mcount;
		index %= this->mcount;
		return (this->mtable [index]);
	}
	return ((oitem *) (0));
}

/*====================================================================*
 *
 *   oitem * operator [] (signed index) const;
 *
 *   return the oitem pointer stored at a relative list position;
 *   return a void pointer if the list is empty;
 *
 *--------------------------------------------------------------------*/

oitem * olist::operator [] (signed index) const 

{
	if (this->mcount > 0) 
	{
		index %= (signed) (this->mcount);
		index += this->mcount;
		index %= this->mcount;
		return (this->mtable [index]);
	}
	return ((oitem *) (0));
}

/*====================================================================*
 *
 *   bool defined (char const * symbol);
 *
 *   return true if mtable[] contains an object having the same name  
 *   as the symbol argument; 
 *
 *--------------------------------------------------------------------*/

bool olist::defined (char const * symbol) 

{
	return (this->indexof (symbol) < this->mcount);
}

/*====================================================================*
 *
 *   bool defined (char const * symbol, char const * string);
 *
 *   return true if mtable[] contains an object having the same name 
 *   as the symbol argument and the same text as the string argument; 
 *
 *--------------------------------------------------------------------*/

bool olist::defined (char const * symbol, char const * string) 

{
	return (this->indexof (symbol, string) < this->mcount);
}

/*====================================================================*
 *
 *   unsigned indexof (char const * symbol);
 *
 *   return the index of an object having the same name as the symbol 
 *   argument; return an index from mstart to mcount where mcount means 
 *   no such object found;
 *
 *--------------------------------------------------------------------*/

unsigned olist::indexof (char const * symbol) 

{
	return (this->select (symbol).index ());
}

/*====================================================================*
 *
 *   unsigned indexof (char const * symbol, char const * string);
 *
 *   return the index if an object having the same name as the symbol 
 *   argument and the same text as the string argument; return an index 
 *   from mstart to mcount where mcount means no such object found;
 *
 *--------------------------------------------------------------------*/

unsigned olist::indexof (char const * symbol, char const * string) 

{
	return (this->select (symbol, string).index ());
}

/*====================================================================*
 *
 *   oitem * item (char const * symbol) 
 *
 *
 *--------------------------------------------------------------------*/

oitem * olist::item (char const * symbol) 

{
	return (this->select (symbol).item ());
}

/*====================================================================*
 *
 *   oitem * item (char const * symbol, char const * string);
 *
 *
 *--------------------------------------------------------------------*/

oitem * olist::item (char const * symbol, char const * string) 

{
	return (this->select (symbol, string).item ());
}

/*====================================================================*
 *
 *   olist & select (char const * symbol);
 *
 *   align mindex to an mtable[] entry having the same name as the 
 *   symbol argument; set mindex to mcount if no matching entry is 
 *   found; 
 *
 *--------------------------------------------------------------------*/

olist & olist::select (char const * symbol) 

{
	this->mlower = this->mstart;
	this->mupper = this->mcount;
	while (this->mlower < this->mupper) 
	{
		this->mindex = (this->mlower + this->mupper) >> 1;
		signed order = (this->morder) (symbol, this->mtable [this->mindex] ->name ());
		if (order < 0) 
		{
			this->mupper = this->mindex - 0;
			continue;
		}
		if (order > 0) 
		{
			this->mlower = this->mindex + 1;
			continue;
		}
		return (* this);
	}
	this->mindex = this->mcount;
	return (* this);
}

/*====================================================================*
 *
 *   unsigned select (char const * symbol, char const * string);
 *
 *   align mindex to an mtable[] entry having the same name as the 
 *   symbol argument and the same text as the string argument; set
 *   mindex to mcount if no matching entry is found; 
 *
 *--------------------------------------------------------------------*/

olist & olist::select (char const * symbol, char const * string) 

{
	signed order;
	this->mlower = this->mstart;
	this->mupper = this->mcount;
	while (this->mlower < this->mupper) 
	{
		this->mindex = (this->mlower + this->mupper) >> 1;
		order = (this->morder) (symbol, this->mtable [this->mindex]->name ());
		if (order < 0) 
		{
			this->mupper = this->mindex - 0;
			continue;
		}
		if (order > 0) 
		{
			this->mlower = this->mindex + 1;
			continue;
		}
		order = (this->morder) (string, this->mtable [this->mindex] ->text ());
		if (order < 0) 
		{
			this->mupper = this->mindex - 0;
			continue;
		}
		if (order > 0) 
		{
			this->mlower = this->mindex + 1;
			continue;
		}
		return (* this);
	}
	this->mindex = this->mcount;
	return (* this);
}

/*====================================================================*
 *
 *   olist & insertitem (moitem * item);
 *
 *   store a new item in mtable provided mlower is not less that 
 *   mupper;
 *
 *   mlower and mupper are used by the fetch method to locate an 
 *   item in mtable; if they cross then the item is missing; 
 *   otherwise, the item is present and should not be inserted 
 *   again; this is a simple check that can be defeated when 
 *   needed;
 *
 *--------------------------------------------------------------------*/

olist & olist::insertitem (oitem * item) 

{
	if (this->mlower >= this->mupper) 
	{
		if (this->mcount >= this->mlimit) 
		{
			oitem ** table = this->mtable;
			this->mlimit = this->mlimit + this->mblock;
			this->mblock = this->mlimit - this->mblock;
			this->mtable = new oitem *[this->mlimit];
			for (this->mindex = this->mstart; this->mindex < this->mlimit; this->mindex++) 
			{
				this->mtable [this->mindex] = table [this->mindex];
			}
			delete [] table;
		}
		for (this->mindex = this->mcount++; this->mindex > this->mlower; this->mindex--) 
		{
			this->mtable [this->mindex] = this->mtable [this->mindex - 1];
		}
		this->mtable [this->mindex] = item;
		this->mlower = this->mstart;
		this->mupper = this->mcount;
	}
	return (* this);
}

/*====================================================================*
 *
 *   olist & removeitem ();
 *
 *   erase the the item stored at the current index position; shift other
 *   items down to fill the void;
 *
 *--------------------------------------------------------------------*/

olist & olist::removeitem () 

{
	oitem * item = this->mtable [this->mindex];
	for (this->mcount--; this->mindex < this->mcount; this->mindex++) 
	{
		this->mtable [this->mindex] = this->mtable [this->mindex + 1];
	}
	this->mtable [this->mindex] = (oitem *) (0);
	delete item;
	return (* this);
}

/*====================================================================*
 *
 *   olist & bound (char const * symbol);
 *
 *
 *--------------------------------------------------------------------*/

olist & olist::bound (char const * symbol) 

{
	if (this->defined (symbol)) 
	{
		this->mlower = this->mupper = this->mindex;
		while ((this->mlower > this->mstart) && ((this->morder) (this->mtable [this->mindex] ->name (), this->mtable [this->mlower - 1] ->name ()) == 0)) 
		{
			this->mlower--;
		}
		while ((this->mupper < this->mcount) && ((this->morder) (this->mtable [this->mindex] ->name (), this->mtable [this->mupper + 0] ->name ()) == 0)) 
		{
			this->mlower++;
		}
	}
	return (* this);
}

/*====================================================================*
 *
 *   olist & clear ();
 *
 *   erase member mtaBle and reset counters; preserve members mtitle and 
 *   morder; 
 *
 *--------------------------------------------------------------------*/

olist & olist::clear () 

{
	delete [] this->mtable;
	this->mtable = new oitem *[this->mlimit];
	this->mstart = 0;
	this->mcount = 0;
	this->mindex = 0;
	this->mlower = 0;
	this->mupper = 0;
	return (* this);
}

/*====================================================================*
 *
 *   olist (signed order (char const *, char const *));
 *
 *
 *--------------------------------------------------------------------*/

olist::olist (signed order (char const *, char const *)) 

{
	this->morder = order;
	this->mtitle = new char [1];
	this->mtitle [0] = (char) (0);
	this->mtable = new oitem *[_LISTSIZE];
	this->mblock = _LISTSIZE;
	this->mlimit = _LISTSIZE;
	this->mstart = 0;
	this->mcount = 0;
	this->mindex = 0;
	this->mlower = 0;
	this->mupper = 0;
	return;
}

/*====================================================================*
 *
 *   olist ();
 *   
 *--------------------------------------------------------------------*/

olist::olist () 

{
	this->morder = std::strcmp;
	this->mtitle = new char [1];
	this->mtitle [0] = (char) (0);
	this->mtable = new oitem *[_LISTSIZE];
	this->mblock = _LISTSIZE;
	this->mlimit = _LISTSIZE;
	this->mstart = 0;
	this->mcount = 0;
	this->mindex = 0;
	this->mlower = 0;
	this->mupper = 0;
	return;
}

/*====================================================================*
 *
 *   ~olist () 
 *   
 *--------------------------------------------------------------------*/

olist::~olist () 

{
	delete [] this->mtitle;
	delete [] this->mtable;
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

