/*====================================================================*
 *
 *   okeep.cpp - implementation of the okeep class.
 *
 *   create and maintain an ordered tree of named nodes where each
 *   node is the head of a linked list of objects;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oKEEP_SOURCE
#define oKEEP_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/okeep.hpp"

/*====================================================================*
 *
 *   void * store (char const * string, void * object);
 *
 *--------------------------------------------------------------------*/

void * okeep::store (char const * string, void * object) 

{
	if (this->mstring == (char *) (0)) 
	{
		this->mstring = new char [strlen (string) + 1];
		std::strcpy (this->mstring, string);
	}
	int order = std::strcmp (string, mstring);
	if (order < 0) 
	{
		if (this->mprior == (okeep *) (0)) 
		{
			this->mprior = new okeep ();
		}
		return (this->mprior->store (string, object));
	}
	if (order > 0) 
	{
		if (this->mafter == (okeep *) (0)) 
		{
			this->mafter = new okeep ();
		}
		return (this->mafter->store (string, object));
	}
	void * pobject = this->mobject;
	this->mobject = object;
	return (pobject);
}

/*====================================================================*
 *
 *   void * fetch (char const * string) const;
 *
 *
 *--------------------------------------------------------------------*/

void * okeep::fetch (char const * string) const 

{
	const okeep * node = this;
	while (node != (okeep *) (0)) 
	{
		int order = std::strcmp (string, node->mstring);
		if (order < 0) 
		{
			node = node->mprior;
			continue;
		}
		if (order > 0) 
		{
			node = node->mafter;
			continue;
		}
		return ((void *) (node->mobject));
	}
	return ((void *) (0));
}

/*====================================================================*
 *
 *   okeep()
 *
 *--------------------------------------------------------------------*/

okeep::okeep () 

{
	mstring = (char *) (0);
	mobject = (void *) (0);
	mprior = (okeep *) (0);
	mafter = (okeep *) (0);
	return;
};

/*====================================================================*
 *
 *   ~okeep()
 *
 *--------------------------------------------------------------------*/

okeep::~okeep () 

{
	delete [] mstring;
	this->mstring = (char *) (0);
	this->mobject = (void *) (0);
	this->mprior = (okeep *) (0);
	this->mafter = (okeep *) (0);
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

