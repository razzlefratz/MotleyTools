/*====================================================================*
 *
 *   osorter.cpp - implementation of the osorter class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSORTER_SOURCE
#define oSORTER_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/osorter.hpp"
#include "../classes/tools.h"

/*====================================================================*
 *
 *   unsigned int osorter::index() const;
 *
 *
 *--------------------------------------------------------------------*/

unsigned int osorter::index () const 

{
	return (this->mindex);
}


/*====================================================================*
 *
 *   unsigned int osorter::start() const;
 *
 *
 *--------------------------------------------------------------------*/

unsigned int osorter::start () const 

{
	return (this->mstart);
}


/*====================================================================*
 *
 *   unsigned int osorter::count() const;
 *
 *
 *--------------------------------------------------------------------*/

unsigned int osorter::count () const 

{
	return (this->mcount);
}


/*====================================================================*
 *
 *   void osorter::next ();
 *
 *
 *--------------------------------------------------------------------*/

void osorter::home () 

{
	this->mindex = this->mstart;
	return;
}

bool osorter::more () 

{
	return (this->mindex < this->mcount);
}

void osorter::next () 

{
	if (this->mindex < this->mcount) 
	{
		this->mindex++;
	}
	return;
}


/*====================================================================*
 *
 *   void osorter::operator ++ (char const *string);
 *
 *
 *--------------------------------------------------------------------*/

void osorter::operator ++ () 

{
	if (this->mindex < this->mcount) 
	{
		this->mindex++;
	}
	return;
}


/*====================================================================*
 *
 *   char const *osorter::operator[] (unsigned int index);
 *
 *
 *--------------------------------------------------------------------*/

char const *osorter::operator [] (unsigned int index) 

{
	return (this->strings (index));
}


/*====================================================================*
 *
 *   bool osorter::operator += (char const *string);
 *
 *
 *--------------------------------------------------------------------*/

bool osorter::operator += (char const *string) 

{
	return (this->insert (string));
}


/*====================================================================*
 *
 *   bool osorter::operator -= (char const *string);
 *
 *
 *--------------------------------------------------------------------*/

bool osorter::operator -= (char const *string) 

{
	return (this->remove (string));
}


/*====================================================================*
 *
 *   bool osorter::insert(char const *string);
 *
 *
 *--------------------------------------------------------------------*/

bool osorter::insert (char const *string) 

{
	if (this->indexof (string) < this->mcount) 
	{
		return (false);
	}
	this->store (string);
	return (true);
}


/*====================================================================*
 *
 *   bool osorter::remove(char const *string);
 *
 *
 *--------------------------------------------------------------------*/

bool osorter::remove (char const *string) 

{
	if (this->indexof (string) < this->mcount) 
	{
		for (this->mcount--; this->mindex < this->mcount; this->mindex++) 
		{
			this->mtable [this->mindex] = this->mtable [this->mindex + 1];
		}
		this->mtable [this->mindex] = (char *) (0);
		return (true);
	}
	return (false);
}


/*====================================================================*
 *
 *   char const *osorter::string();
 *
 *
 *--------------------------------------------------------------------*/

char const *osorter::string () 

{
	return (this->mindex < this->mcount? this->mtable [this->mindex]: this->mtable [this->mcount]);
}


/*====================================================================*
 *
 *   char const *osorter::strings(unsigned index);
 *
 *
 *--------------------------------------------------------------------*/

char const *osorter::strings (unsigned index) 

{
	return (index < this->mcount? this->mtable [index]: this->mtable [this->mcount]);
}


/*====================================================================*
 *
 *   bool osorter::defined(char const *string);
 *
 *   return logical true if the string argument is a sorted member;
 *
 *--------------------------------------------------------------------*/

bool osorter::defined (char const *string) 

{
	return (this->indexof (string) < this->mcount);
}


/*====================================================================*
 *
 *   unsigned int osorter::indexof(char const *string);
 *
 *
 *--------------------------------------------------------------------*/

unsigned int osorter::indexof (char const *string) 

{
	this->mlower = this->mstart;
	this->mupper = this->mcount;
	while (this->mlower < this->mupper) 
	{
		this->mindex = (this->mlower + this->mupper) >> 1;
		signed order = (this->morder) (string, this->mtable [this->mindex]);
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
		return (this->mindex);
	}
	return (this->mcount);
}


/*====================================================================*
 *
 *   osorter & osorter::store(char const *string);
 *
 *
 *--------------------------------------------------------------------*/

osorter & osorter::store (char const *string) 

{
	if (this->mlower >= this->mupper) 
	{
		if (this->mcount >= this->mlimit) 
		{
			char const **otable = this->mtable;
			this->mtable = new char const *[this->mlimit + this->mblock];
			for (this->mindex = this->mstart; this->mindex < this->mlimit; this->mindex++) 
			{
				this->mtable [this->mindex] = otable [this->mindex];
			}
			this->mlimit = this->mlimit + this->mblock;
			this->mblock = this->mlimit - this->mblock;
			delete [] otable;
		}
		for (this->mindex = this->mcount++; this->mindex > this->mlower; --this->mindex) 
		{
			this->mtable [this->mindex] = this->mtable [this->mindex - 1];
		}
		this->mtable [this->mindex] = new char [strlen (string) + 1];
		strcpy ((char *) (this->mtable [this->mindex]), string);
		this->mtable [this->mcount] = (char *) (0);
		this->mlower = this->mstart;
		this->mupper = this->mcount;
	}
	return (*this);
}


/*====================================================================*
 *
 *   bool listdefine (LIST * list, char const *string, char const c)
 *
 *   list.h
 *
 *   split a copy of the string argument into substrings at each occurance 
 *   of character c; add each substring to the list using listappend();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osorter & osorter::define (char string [], unsigned char c) 

{
	char *sp;
	if (string != (char *) (0)) 
	{
		for (sp = string; *sp != (char) (0); sp++) 
		{
			if (*sp == c) 
			{
				*sp = (char) (0);
				this->store (string);
				string = sp + 1;
			}
		}
		if (sp > string) 
		{
			this->store (string);
		}
	}
	return (*this);
}


/*====================================================================*
 *
 *   osorter & osorter::clear();
 *
 *
 *--------------------------------------------------------------------*/

osorter & osorter::clear () 

{
	delete [] mtable;
	this->mtable = new char const *[this->mlimit];
	this->mcount = 0;
	this->mstart = 0;
	this->mlower = 0;
	this->mupper = 0;
	this->mindex = 0;
	return (*this);
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

osorter::osorter (int order (char const *, char const *)) 

{
	this->morder = order;
	this->mtable = new char const *[_LISTSIZE];
	this->mlimit = _LISTSIZE;
	this->mblock = _LISTSIZE;
	this->mstart = 0;
	this->mcount = 0;
	this->mlower = 0;
	this->mupper = 0;
	this->mindex = 0;
}

osorter::osorter () 

{
	this->morder = std::strcmp;
	this->mtable = new char const *[_LISTSIZE];
	this->mblock = _LISTSIZE;
	this->mlimit = _LISTSIZE;
	this->mstart = 0;
	this->mcount = 0;
	this->mlower = 0;
	this->mupper = 0;
	this->mindex = 0;
}

osorter::~osorter () 

{
	delete [] this->mtable;
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

