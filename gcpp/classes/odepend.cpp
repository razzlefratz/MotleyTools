/*====================================================================*
 *
 *   odepend.cpp - implementation of the odepend class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oDEPEND_SOURCE
#define oDEPEND_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/odepend.hpp"

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

odepend odepend::nodes;
oqueue odepend::queue;

/*====================================================================*
 *
 *   odepend & populate (char colon, char comma, bool invert);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odepend & odepend::populate (char colon, char comma, bool invert) 

{
	char one [oDEPEND_SYMBOL_LENGTH] = "";
	char two [oDEPEND_SYMBOL_LENGTH] = "";
	char * sp;
	signed c;
	while ((c = std::cin.get ()) != EOF) 
	{
		for (sp = one; oascii::nobreak (c); c = std::cin.get ()) 
		{
			if ((char)(c) == colon) 
			{
				c = std::cin.get ();
				break;
			}
			if ((sp - one) < (signed) (sizeof (one) - 2)) 
			{
				* sp++ = (char) (c);
			}
		}
		* sp = (char) (0);
		for (sp = two; oascii::nobreak (c); c = std::cin.get ()) 
		{
			if ((char)(c) == comma) 
			{
				c = std::cin.get ();
				break;
			}
			if ((sp - two) < (signed) (sizeof (two) - 2)) 
			{
				* sp++ = (char) (c);
			}
		}
		* sp = (char) (0);
		if (oascii::nobreak (c)) 
		{
			c = std::cin.get ();
		}
		if (invert) 
		{
			this->connect (two, one);
		}
		else
		{
			this->connect (one, two);
		}
	}
	return (* this);
}

/*====================================================================*
 *
 *   odepend & connect(char const * one, char const * two);
 *
 *   relate one node to another, creating the nodes, if missing; the
 *   first node is stored in the main tree and the second is stored
 *   in the associated subordinate tree;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odepend & odepend::connect (char const * one, char const * two) 

{
	odepend * node = this->store (one);
	if (!node->mbelow) 
	{
		node->mbelow = new odepend (two);
	}
	else
	{
		node->mbelow->store (two);
	}
	return (* this);
}

/*====================================================================*
 *
 *   odepend * store (char const * nodename);
 *
 *   store nodename in this dependency tree, if missing; return the 
 *   new or existing node address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odepend * odepend::store (char const * nodename) 

{
	odepend * node = this;
	while (node) 
	{
		signed order = std::strcmp (nodename, node->mstring);
		if (order < 0) 
		{
			if (!node->mprior) 
			{
				node->mprior = new odepend (nodename);
			}
			node = node->mprior;
			continue;
		}
		if (order > 0) 
		{
			if (!node->mafter) 
			{
				node->mafter = new odepend (nodename);
			}
			node = node->mafter;
			continue;
		}
		break;
	}
	return (node);
}

/*====================================================================*
 *
 *   odepend & odepend::fetch(char const *nodename);
 *
 *   return the address of the named node if present or (odepend *)(0) if 
 *   missing; this function is rarely used but provided for completeness;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odepend * odepend::fetch (char const * nodename) 

{
	odepend * node = this;
	while (node) 
	{
		signed order = std::strcmp (nodename, node->mstring);
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
		break;
	}
	return (node);
}

/*====================================================================*
 *
 *   odepend & enumerate();
 *
 *   print nodenames in alphabetical order, one name per line; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odepend & odepend::enumerate () 

{
	if (this->mprior != (odepend *)(0)) 
	{
		this->mprior->enumerate ();
	}
	std::cout << this->mstring << std::endl;
	if (this->mafter) 
	{
		this->mafter->enumerate ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   odepend & structure();
 *
 *   print major nodenames in alphabetical order, one name per line, 
 *   with minor nodenames indented below each major nodename; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odepend & odepend::structure () 

{
	if (this->mprior != (odepend *)(0)) 
	{
		this->mprior->structure ();
	}
	std::cout << this->mstring << std::endl;
	if (this->mbelow) 
	{
		this->mbelow->component ();
		std::cout << std::endl;
	}
	if (this->mafter) 
	{
		this->mafter->structure ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   odepend & component();
 *
 *   print minor node names in alphabetical order, one name per line, 
 *   indented by horizontal tab;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odepend & odepend::component () 

{
	if (this->mprior != (odepend *)(0)) 
	{
		this->mprior->component ();
	}
	std::cout << "\t" << this->mstring << std::endl;
	if (this->mafter) 
	{
		this->mafter->component ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   odepend & targets ();
 *
 *   print major nodenames in alphabetical order, one name per line, 
 *   followed by minor nodenames in alphabetical  order;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odepend & odepend::targets () 

{
	if (this->mprior != (odepend *)(0)) 
	{
		this->mprior->targets ();
	}
	std::cout << odepend::basename (this->mstring) << ":";
	std::cout << " " << odepend::basename (this->mstring);
	if (this->mbelow) 
	{
		this->mbelow->sources ();
	}
	std::cout << std::endl;
	if (this->mafter) 
	{
		this->mafter->targets ();
	}
	return (* this);
}

/*====================================================================*
 *
 *   odepend & sources();
 *
 *   print minor node names in alphabetical order seperated by spaces;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odepend & odepend::sources () 

{
	if (this->mprior != (odepend *)(0)) 
	{
		this->mprior->sources ();
	}
	std::cout << " " << odepend::basename (this->mstring);
	if (this->mafter) 
	{
		this->mafter->sources ();
	}
	return (* this);
}

/*====================================================================*
 * 
 *   odepend (char const * string);
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odepend::odepend (char const * string) 

{
	this->mprior = (odepend *) (0);
	this->mafter = (odepend *) (0);
	this->mbelow = (odepend *) (0);
	this->mstring = new char [strlen (string) +1];
	std::strcpy (this->mstring, string);
	odepend::queue.append ((void *) (this->mstring));
	return;
}

/*====================================================================*
 * 
 *   odepend();
 *
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odepend::odepend () 

{
	this->mprior = (odepend *) (0);
	this->mafter = (odepend *) (0);
	this->mbelow = (odepend *) (0);
	this->mstring = new char [1];
	this->mstring [0] = (char)(0);
	return;
}

/*====================================================================*
 * 
 *   ~odepend();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odepend::~odepend () 

{
	this->mprior = (odepend *) (0);
	this->mafter = (odepend *) (0);
	this->mbelow = (odepend *) (0);
	delete [] this->mstring;
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

