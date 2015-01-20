/*====================================================================*
 *
 *   otree.cpp - implementation of the otree class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oTREE_SOURCE
#define oTREE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/otree.hpp"
#include "../../gcc/strlib/strlib.h"

/*====================================================================*
 *
 *   char const * nodename () const;
 *
 *   return the node nodename as a string constant;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * otree::nodename () const

{
	return (this->msymbol);
}

/*====================================================================*
 *
 *   char const * nodetext () const;
 *
 *   return the node string as a string constant;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * otree::nodetext () const

{
	return (this->mstring);
}

/*====================================================================*
 *
 *   otree & nodetext (char const * nodetext);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree & otree::nodetext (char const * nodetext)

{
	if (std::strcmp (this->mstring, nodetext))
	{
		delete [] this->mstring;
		this->mstring = new char [std::strlen (nodetext) + 1];
		std::strcpy (this->mstring, nodetext);
	}
	return (* this);
}

/*====================================================================*
 *
 *   void *nodedata () const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void * otree::nodedata () const

{
	return (this->mobject);
}

/*====================================================================*
 *
 *   otree & nodedata (void *object);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree & otree::nodedata (void * nodedata)

{
	this->mobject = nodedata;
	return (* this);
}

/*====================================================================*
 *
 *   long index () const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

long otree::index () const

{
	return (this->mindex);
}

/*====================================================================*
 *
 *   otree & index (long index);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree & otree::index (long index)

{
	this->mindex = index;
	return (* this);
}

/*====================================================================*
 *
 *   long count () const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

long otree::count () const

{
	return (this->mcount);
}

/*====================================================================*
 *
 *   otree & count (long count);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree & otree::count (long count)

{
	this->mcount = count;
	return (* this);
}

/*====================================================================*
 *
 *   long level () const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

long otree::level () const

{
	return (this->mlevel);
}

/*====================================================================*
 *
 *   otree & level (long level);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree & otree::level (long level)

{
	this->mlevel = level;
	return (* this);
}

/*====================================================================*
 *
 *   long first () const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

long otree::first () const

{
	return (this->mindex);
}

/*====================================================================*
 *
 *   long final () const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

long otree::final () const

{
	return (this->mcount);
}

/*====================================================================*
 *
 *   otree * nodeabove () const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::nodeabove () const

{
	return (this->mabove);
}

/*====================================================================*
 *
 *   otree & nodeabove (otree *node);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree & otree::nodeabove (otree * node)

{
	this->mabove = node;
	return (* this);
}

/*====================================================================*
 *
 *   otree * nodeprior () const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::nodeprior () const

{
	return (this->mprior);
}

/*====================================================================*
 *
 *   otree & nodeprior (otree *node);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree & otree::nodeprior (otree * node)

{
	this->mabove = node;
	return (* this);
}

/*====================================================================*
 *
 *   otree * nodeafter () const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::nodeafter () const

{
	return (this->mafter);
}

/*====================================================================*
 *
 *   otree & nodeafter (otree * node);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree & otree::nodeafter (otree * node)

{
	this->mabove = node;
	return (* this);
}

/*====================================================================*
 *
 *   otree * nodebelow () const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::nodebelow () const

{
	return (this->mbelow);
}

/*====================================================================*
 *
 *   otree & nodebelow (otree * node);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree & otree::nodebelow (otree * node)

{
	this->mabove = node;
	return (* this);
}

/*====================================================================*
 *
 *   char *strings (long index) const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char * otree::strings (long index) const

{
	otree * node = this->nodes (index);
	return (node? node->mstring: (char *) (0));
}

/*====================================================================*
 *
 *   void *objects (long index) const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void * otree::objects (long index) const

{
	otree * node = this->nodes (index);
	return (node? node->mobject: (void *) (0));
}

/*====================================================================*
 *
 *   otree * root () const;
 *
 *   return the tree root node;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::root () const

{
	const otree * node = this;
	node = node->home ();
	node = node->head ();
	return ((otree *) (node));
}

/*====================================================================*
 *
 *   otree * home () const;
 *
 *   return the home node; the home node is branch parent;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::home () const

{
	const otree * node = this;
	while (node->mabove)
	{
		node = node->mabove;
	}
	return ((otree *) (node));
}

/*====================================================================*
 *
 *   otree * head () const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::head () const

{
	const otree * node = this;
	while (node->mprior)
	{
		node = node->mprior;
	}
	return ((otree *) (node));
}

/*====================================================================*
 *
 *   otree * tail () const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::tail () const

{
	const otree * node = this;
	while (node->mafter)
	{
		node = node->mafter;
	}
	return ((otree *) (node));
}

/*====================================================================*
 *
 *   otree * nodes (long index) const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::nodes (long index) const

{
	const otree * node = this;
	while ((node) && (node->mindex != index))
	{
		if (index < node->mindex)
		{
			if (node->mabove)
			{
				node = node->mabove;
			}
			else 
			{
				node = node->mprior;
			}
			continue;
		}
		if (! node->mafter)
		{
			node = node->mbelow;
			continue;
		}
		if (index < node->mafter->mindex)
		{
			node = node->mbelow;
			continue;
		}
		node = node->mafter;
	}
	return ((otree *) (node));
}

/*====================================================================*
 *
 *   otree * insertabove (char const * nodename);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::insertabove (char const * nodename)

{
	otree * node = new otree (nodename);
	if (this->mabove)
	{
		node->mabove = this->mabove;
		node->mabove->mbelow = node;
	}
	this->mabove = node;
	node->mbelow = this;
	return (node);
}

/*====================================================================*
 *
 *   otree * insertprior (char const * nodename);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::insertprior (char const * nodename)

{
	otree * node = new otree (nodename);
	if (this->mprior)
	{
		this->mprior->mafter = node;
		node->mprior = this->mprior;
	}
	else if (this->mabove)
	{
		this->mabove->mbelow = node;
		node->mabove = this->mabove;
	}
	this->mprior = node;
	node->mafter = this;
	return (node);
}

/*====================================================================*
 *
 *   otree * insertafter (char const * nodename);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::insertafter (char const * nodename)

{
	otree * node = new otree (nodename);
	node->mabove = this->mabove;
	if (this->mafter)
	{
		this->mafter->mprior = node;
		node->mafter = this->mafter;
	}
	this->mafter = node;
	node->mprior = this;
	return (node);
}

/*====================================================================*
 *
 *   otree * insertbelow (char const * nodename);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::insertbelow (char const * nodename)

{
	otree * node = new otree (nodename);
	if (this->mbelow)
	{
		this->mbelow->mabove = node;
		node->mbelow = this->mbelow;
	}
	this->mbelow = node;
	node->mabove = this;
	return (node);
}

/*====================================================================*
 *
 *   otree * appendprior (char const * nodename);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::appendprior (char const * nodename)

{
	return (this->head () ->insertprior (nodename));
}

/*====================================================================*
 *
 *   otree * appendafter (char const * nodename);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::appendafter (char const * nodename)

{
	return (this->tail () ->insertafter (nodename));
}

/*====================================================================*
 *
 *   otree *appendbelow (char const * nodename);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::appendbelow (char const * nodename)

{
	otree * node = new otree (nodename);
	if (this->mbelow)
	{
		otree * temp = this->mbelow;
		while (temp->mafter)
		{
			temp = temp->mafter;
		}
		temp->mafter = node;
		node->mprior = temp;
		node->mabove = this;
	}
	else 
	{
		this->mbelow = node;
		node->mabove = this;
	}
	return (node);
}

/*====================================================================*
 *
 *   otree * createafter (char const * string, void const * object, const int order);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::createafter (char const * nodename, const int order)

{
	otree * node = this;
	otree * temp;
	if (order) while (node)
	{
		int path = std::strcmp (nodename, node->msymbol);
		if (path < 0)
		{
			if (! node->mafter)
			{
				temp = new otree (nodename);
				temp->mabove = node->mabove;
				temp->mprior = node;
				node->mafter = temp;
			}
			node = node->mafter;
			continue;
		}
		if (path > 0)
		{
			temp = new otree (nodename);
			if (node->mprior)
			{
				node->mprior->mafter = temp;
				temp->mprior = node->mprior;
			}
			else if (node->mabove)
			{
				node->mabove->mbelow = temp;
				temp->mabove = node->mabove;
			}
			node->mprior = temp;
			temp->mafter = node;
			continue;
		}
		break;
	}
	else while (std::strcmp (nodename, node->msymbol))
	{
		if (node->mafter)
		{
			temp = new otree (nodename);
			temp->mabove = node->mabove;
			temp->mprior = node;
			node->mafter = temp;
		}
		node = node->mafter;
	}
	return (node);
}

/*====================================================================*
 *
 *   otree * createbelow (char const * nodename, const int order);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::createbelow (char const * nodename, const int order)

{
	otree * node = this->mbelow;
	if (this->mbelow)
	{
		node = node->createafter (nodename, order);
	}
	else 
	{
		node = new otree (nodename);
		node->mabove = this;
		this->mbelow = node;
	}
	return (node);
}

/*====================================================================*
 *
 *   otree & connect ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree & otree::connect ()

{
	if (this->mbelow)
	{
		this->mbelow->mabove = this;
		this->mbelow->connect ();
	}
	if (this->mafter)
	{
		this->mafter->mprior = this;
		this->mbelow->connect ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   long reorder (long index, long level);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

long otree::reorder (long index, long level)

{
	otree * node = this;
	while (node)
	{
		node->mlevel = level;
		node->mindex = index++;
		node->mcount = index;
		if (node->mbelow)
		{
			node->mindex = this->mbelow->reorder (index, level + 1);
		}
		node->mcount = index - node->mcount;
		node = node->mafter;
	}
	return (index);
}

/*====================================================================*
 *
 *   otree  & outline () const
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree & otree::outline ()

{
	static signed margin = 0;
	otree * node = this;
	while (node)
	{
		for (int column = 0; column < margin; column++)
		{
			std::cout << "\t";
		}
		std::cout << node->msymbol << std::endl;
		if (node->mbelow)
		{
			margin++;
			node->mbelow->outline ();
			margin--;
		}
		node = node->mafter;
	}
	return (* this);
}

/*====================================================================*
 *
 *   otree * findnext (char const * nodename) const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::findnext (char const * nodename) const

{
	const otree * node = this;
	do 
	{
		node = node->mafter;
	}
	while (node && std::strcmp (node->msymbol, nodename));
	return ((otree *) (node));
}

/*====================================================================*
 *
 *   otree *findprev (char const * nodename) const;
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::findprev (char const * nodename) const

{
	const otree * node = this;
	do 
	{
		node = node->mprior;
	}
	while (node && std::strcmp (node->msymbol, nodename));
	return ((otree *) (node));
}

/*====================================================================*
 *
 *   char * otree::pathname (char buffer [], size_t length, char extender);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char * otree::pathname (char buffer [], size_t length, char extender)

{
	otree * node = this;
	char * string;
	buffer += length--;
	* -- buffer = (char) (0);
	while (node->mabove)
	{
		for (string = node->msymbol; * string; string++);
		while ((string > node->msymbol) && (length))
		{
			* -- buffer = * -- string;
			length--;
		}
		* -- buffer = extender;
		node = node->mabove;
	}
	for (string = node->msymbol; * string; string++);
	while ((string > node->msymbol) && (length))
	{
		* -- buffer = * -- string;
		length--;
	}
	return (buffer);
}

/*====================================================================*
 *
 *   otree * createpath (char const * pathname, char extender);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::createpath (char const * pathname, char extender)

{
	otree * node = this;
	otree * temp;
	char const * nodename = pathname;
	while ((* pathname) && (* pathname != extender))
	{
		pathname++;
	}
	while (node && std::strncmp (node->msymbol, nodename, pathname - nodename))
	{
		if (! node->mafter)
		{
			temp = new otree (nodename, pathname - nodename);
			temp->mabove = node->mabove;
			temp->mprior = node;
			node->mafter = temp;
		}
		node = node->mafter;
	}
	if (* pathname)
	{
		if (node->mbelow)
		{
			return (node->mbelow->createpath (++ pathname, extender));
		}
		while (! node->mbelow && * pathname)
		{
			temp = new otree (nodename, pathname - nodename);
			temp->mabove = node;
			node->mbelow = temp;
		}
	}
	return (node);
}

/*====================================================================*
 *
 *   otree * selectpath (char const * pathname, char extender);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree * otree::selectpath (char const * pathname, char extender)

{
	otree * node = this;
	char const * nodename = pathname;
	while ((* pathname) && (* pathname != extender))
	{
		pathname++;
	}
	while (node && std::strncmp (this->msymbol, nodename, pathname - nodename))
	{
		node = node->mafter;
	}
	if ((node) && (* pathname))
	{
		return (node->mbelow->selectpath (++ pathname, extender));
	}
	return (node);
}

/*====================================================================*
 *
 *   otree (char const * nodename, void const * nodedata);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree::otree (char const * nodename, void const * nodedata)

{
	this->msymbol = new char [std::strlen (nodename) + 1];
	std::strcpy (this->msymbol, nodename);
	this->msymbol = new char [1];
	this->mstring [0] = (char) (0);
	this->mobject = (void *) (nodedata);
	this->mabove = (otree *) (0);
	this->mprior = (otree *) (0);
	this->mafter = (otree *) (0);
	this->mbelow = (otree *) (0);
	return;
}

/*====================================================================*
 *
 *   otree (char const * nodename, size_t length);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree::otree (char const nodename [], size_t length)

{
	this->msymbol = new char [length + 1];
	std::strncpy (this->msymbol, nodename, length);
	this->msymbol [length] = (char) (0);
	this->mstring = new char [1];
	this->mstring [0] = (char) (0);
	this->mobject = (void *) (0);
	this->mabove = (otree *) (0);
	this->mprior = (otree *) (0);
	this->mafter = (otree *) (0);
	this->mbelow = (otree *) (0);
	return;
}

/*====================================================================*
 *
 *   otree (char const * nodename);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree::otree (char const * nodename)

{
	this->msymbol = new char [std::strlen (nodename) + 1];
	std::strcpy (this->msymbol, nodename);
	this->mstring = new char [1];
	this->mstring [0] = (char) (0);
	this->mobject = (void *) (0);
	this->mabove = (otree *) (0);
	this->mprior = (otree *) (0);
	this->mafter = (otree *) (0);
	this->mbelow = (otree *) (0);
	return;
}

/*====================================================================*
 *
 *   otree ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

otree::~ otree ()

{
	delete [] this->msymbol;
	delete [] this->mstring;
	this->mstring = (char *) (0);
	this->mobject = (void *) (0);
	this->mabove = (otree *) (0);
	this->mprior = (otree *) (0);
	this->mafter = (otree *) (0);
	this->mbelow = (otree *) (0);
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif



