/*====================================================================*
 *
 *   othread.cpp - implementation of the othread class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oTHREAD_SOURCE
#define oTHREAD_SOURCE

/*====================================================================*
 *   custom header pages;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom source pages;
 *--------------------------------------------------------------------*/

#include "../classes/othread.hpp"

/*====================================================================*
 *
 *   unsigned count() const;
 *
 *
 *--------------------------------------------------------------------*/

unsigned othread::count () const

{
	unsigned counter = 0;
	othread * page = this->mafter;
	while (page != this)
	{
		page = page->mafter;
		counter++;
	}
	return (counter);
}

/*====================================================================*
 *
 *   bool isempty () const;
 *
 *
 *--------------------------------------------------------------------*/

bool othread::isempty () const

{
	return (this == this->mafter);
}

/*====================================================================*
 *
 *   char const *name () const;
 *
 *
 *--------------------------------------------------------------------*/

char const * othread::name () const

{
	return (this->mname);
}

/*====================================================================*
 *
 *   char const *text () const;
 *
 *
 *--------------------------------------------------------------------*/

char const * othread::text () const

{
	return (this->mtext);
}

/*====================================================================*
 *
 *   char const *page () const;
 *
 *
 *--------------------------------------------------------------------*/

char const * othread::page () const

{
	return (this->mpage);
}

/*====================================================================*
 *
 *   othread & name (char const *string);
 *
 *
 *--------------------------------------------------------------------*/

othread & othread::name (char const * string)

{
	this->mname = otext::replace (this->mname, string);
	return (* this);
}

/*====================================================================*
 *
 *   othread & text (char const *string);
 *
 *
 *--------------------------------------------------------------------*/

othread & othread::text (char const * string)

{
	this->mtext = otext::replace (this->mtext, string);
	return (* this);
}

/*====================================================================*
 *
 *   othread & page (char const *string);
 *
 *
 *--------------------------------------------------------------------*/

othread & othread::page (char const * string)

{
	this->mpage = otext::replace (this->mpage, string);
	return (* this);
}

/*====================================================================*
 *
 *   othread *above () const;
 *
 *
 *--------------------------------------------------------------------*/

othread * othread::above () const

{
	return (this->mabove);
}

/*====================================================================*
 *
 *   othread *prior () const;
 *
 *
 *--------------------------------------------------------------------*/

othread * othread::prior () const

{
	return (this->mprior);
}

/*====================================================================*
 *
 *   othread *after () const;
 *
 *
 *--------------------------------------------------------------------*/

othread * othread::after () const

{
	return (this->mafter);
}

/*====================================================================*
 *
 *   othread *below () const;
 *
 *
 *--------------------------------------------------------------------*/

othread * othread::below () const

{
	return (this->mbelow);
}

/*====================================================================*
 *
 *   othread *other () const;
 *
 *
 *
 *--------------------------------------------------------------------*/

othread * othread::other () const

{
	return (this->mother);
}

/*====================================================================*
 *
 *   othread & insert (othread * thread);
 *
 *
 *--------------------------------------------------------------------*/

othread & othread::insert (othread * thread)

{
	thread->mprior = this;
	thread->mafter = this->mafter;
	this->mafter->mprior = thread;
	this->mafter = thread;
	return (* this);
}

/*====================================================================*
 *
 *   othread & append (othread * thread);
 *
 *
 *--------------------------------------------------------------------*/

othread & othread::append (othread * thread)

{
	thread->mafter = this;
	thread->mprior = this->mafter;
	this->mprior->mafter = thread;
	this->mprior = thread;
	return (* this);
}

/*====================================================================*
 *
 *   othread & remove ();
 *
 *
 *--------------------------------------------------------------------*/

othread & othread::remove ()

{
	if (this != this->mafter)
	{
		delete this->mafter;
	}
	return (* this);
}

/*====================================================================*
 *
 *   othread & unwind ();
 *
 *
 *--------------------------------------------------------------------*/

othread & othread::unwind ()

{
	if (this != this->mprior)
	{
		delete this->mprior;
	}
	return (* this);
}

/*====================================================================*
 *
 *   othread & attach (othread * other);
 *
 *
 *--------------------------------------------------------------------*/

othread & othread::attach (othread * other)

{
	othread * thread = other->mafter;
	other->mafter = this->mafter;
	this->mafter = thread;
	thread = other->mprior;
	other->mprior = this->mprior;
	this->mprior = thread;
	return (* other);
}

/*====================================================================*
 *
 *   othread & detach ();
 *
 *
 *--------------------------------------------------------------------*/

othread & othread::detach ()

{
	this->mafter->mprior = this->mprior;
	this->mprior->mafter = this->mafter;
	this->mprior = this;
	this->mafter = this;
	return (* this);
}

/*====================================================================*
 *
 *   othread & clear ();
 *
 *
 *--------------------------------------------------------------------*/

othread & othread::clear ()

{
	while (this != this->mafter)
	{
		delete this->mafter;
	}
	return (* this);
}

/*====================================================================*
 *
 *   char *copy (char const *string);
 *
 *
 *--------------------------------------------------------------------*/

char * othread::copy (char const * string)

{
	char * buffer = new char [strlen (string) +  1];
	strcpy (buffer, string);
	return (buffer);
}

/*====================================================================*
 *
 *   othread (char const *name, char const *text, char const *page);
 *
 *
 *--------------------------------------------------------------------*/

othread::othread (char const * name, char const * text, char const * page)

{
	this->mname = otext::save (name);
	this->mtext = otext::save (text);
	this->mpage = otext::save (page);
	this->mabove = (othread *) (0);
	this->mbelow = (othread *) (0);
	this->mprior = this;
	this->mafter = this;
}

/*====================================================================*
 *
 *   othread ();
 *
 *
 *--------------------------------------------------------------------*/

othread::othread ()

{
	this->mname = otext::save ("index.html");
	this->mtext = otext::save ("index.html");
	this->mpage = otext::save ("index.html");
	this->mabove = (othread *) (0);
	this->mbelow = (othread *) (0);
	this->mprior = this;
	this->mafter = this;
}

/*====================================================================*
 *
 *   ~othread ();
 *
 *
 *--------------------------------------------------------------------*/

othread::~ othread ()

{
	if (this->mabove)
	{
		this->mabove->mbelow = this->mbelow;
	}
	if (this->mbelow)
	{
		this->mbelow->mabove = this->mabove;
	}
	this->mafter->mprior = this->mprior;
	this->mprior->mafter = this->mafter;
	this->mprior = (othread *) (0);
	this->mafter = (othread *) (0);
	this->mabove = (othread *) (0);
	this->mbelow = (othread *) (0);
	delete this->mname;
	delete this->mtext;
	delete this->mpage;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif



