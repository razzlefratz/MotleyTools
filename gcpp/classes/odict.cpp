/*====================================================================*
 *
 *   odict.cpp - implementation of the odict class.
 *   
 *   this object implements a symbol table that supports scoped
 *   definitions using the define() and revert() methods;
 *
 *   the symbol table is implemented as a binary tree where each 
 *   node maintains a stack of definition strings; the stacks are 
 *   implemented using circular linked list where the tail points 
 *   to the stack top; the symbol name is stored in the list tail 
 *   which then points to the most recent definition, which could
 *   be the symbol name; a symbol is undefined when it is its own
 *   definition; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oDICTIONARY_SOURCE
#define oDICTIONARY_SOURCE

/*====================================================================*
 *   system header files; 
 *--------------------------------------------------------------------*/

#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../classes/odict.hpp"

/*====================================================================*
 *
 *   odict & define (char const *symbol, char const *string);
 *
 *   define symbol as string; create symbol if missing or redefine
 *   symbol if already present; return the object address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odict & odict::define (char const * symbol, char const * string) 

{

#ifdef CMASSOC_SAFEMODE

	if (symbol == (char const *) (0)) 
	{
		return (* this);
	}
#endif

	odict * node = this;
	while (node != (odict *) (0)) 
	{
		signed order = odict::comp (symbol, node->msymbol);
		if (order < 0) 
		{
			if (node->mprior == (odict *) (0)) 
			{
				node->mprior = new odict (symbol);
			}
			node = node->mprior;
			continue;
		}
		if (order > 0) 
		{
			if (node->mafter == (odict *) (0)) 
			{
				node->mafter = new odict (symbol);
			}
			node = node->mafter;
			continue;
		}
		delete [] node->mstring;
		node->mstring = new char [strlen (string) + 1];
		std::strcpy (node->mstring, string);
		break;
	}
	return (* this);
}


/*====================================================================*
 *  
 *   bool defined (char const *symbol) const;
 *
 *   return true if symbol is present and has a current definition;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool odict::defined (char const * symbol) const 

{
	return (odict::node (symbol));
}


/*====================================================================*
 *  
 *   char const *lookup (char const *symbol) const;
 *
 *   return the symbol definition (if one exists) or (char *)(0) if
 *   symbol is undefined; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * odict::lookup (char const * symbol) const 

{
	const odict * node = odict::node (symbol);
	if (node != (odict *) (0)) 
	{
		return (node->mstring);
	}
	return ((char const *) (0));
}


/*====================================================================*
 *  
 *   char const *expand (char const *symbol) const;
 *
 *   return the symbol definition (if one exists) or symbol (itself)
 *   symbol is undefined;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * odict::expand (char const * symbol) const 

{
	const odict * node = odict::node (symbol);
	if (node != (odict *) (0)) 
	{
		return (node->mstring);
	}
	return (symbol);
}


/*====================================================================*
 *
 *   odict & enumerate ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odict & odict::enumerate () 

{
	if (this->mprior != (odict *) (0)) 
	{
		this->mprior->enumerate ();
	}
	std::cout << this->msymbol << "=" << this->mstring << std::endl;
	if (this->mafter != (odict *) (0)) 
	{
		this->mafter->enumerate ();
	}
	return (* this);
}


/*====================================================================*
 *
 *   odict & clear ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odict & odict::clear () 

{
	delete [] this->msymbol;
	delete [] this->mstring;
	delete this->mprior;
	delete this->mafter;
	this->mprior = (odict *) (0);
	this->mafter = (odict *) (0);
	return (* this);
}


/*====================================================================*
 *
 *   odict * node (char const *symbol);
 *
 *   find symbol in the tree using an inorder search; return the 
 *   node address or NULL if missing;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

const odict * odict::node (char const * symbol) const 

{
	const odict * node = this;

#ifdef CMASSOC_SAFEMODE

	if (symbol == (char const *) (0)) 
	{
		return ((odict *) (0));
	}
#endif

	while (node != (odict *) (0)) 
	{
		signed order = odict::comp (symbol, node->msymbol);
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
 *   signed comp (register char const *string1, register char const *string2);
 *
 *   compare two strings and return a negative, zero or positive result
 *   to indicate that the first string precedes, matches or follows the
 *   the second using dictionary collating sequence;
 *
 *   in a 'dictionary' collating sequence, a lower case letter precedes
 *   the upper case counterpart.
 *
 *   ... a < A < b < B ... < z < Z ...
 *
 *   this implementation always returns either -1, 0 or 1;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed odict::comp (register char const * string1, register char const * string2) 

{

#ifdef CMASSOC_SAFEMODE

	if (string1 == string2) 
	{
		return (0);
	}
	if (string1 == (char *) (0)) 
	{
		return (-1);
	}
	if (string2 == (char *) (0)) 
	{
		return (+1);
	}
#endif

	while (* string1 == * string2) 
	{
		if (* string1 == (char) (0)) 
		{
			return (0);
		}
		string1++;
		string2++;
	}
	if (toupper (* string1) != toupper (* string2)) 
	{
		return (toupper (* string1) < toupper (* string2)? -1: +1);
	}
	return (* string1 > * string2? -1: +1);
}


/*====================================================================*
 *
 *  void  odict(char const *symbol);
 *
 *   initialize this symbol with an empty symbol name and definition
 *   string; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odict::odict (char const * symbol) 

{
	this->msymbol = new char [strlen (symbol) + 1];
	std::strcpy (this->msymbol, symbol);
	this->mstring = new char [1];
	this->mstring [0] = (char)(0);
	this->mprior = (odict *) (0);
	this->mafter = (odict *) (0);
	return;
}


/*====================================================================*
 *
 *   void odict(char const *symbol, char const *string);
 *
 *   initialize this symbol with the given symbol name and string 
 *   definition;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odict::odict (char const * symbol, char const * string) 

{
	this->msymbol = new char [strlen (symbol) + 1];
	std::strcpy (this->msymbol, symbol);
	this->mstring = new char [strlen (string) + 1];
	std::strcpy (this->mstring, string);
	this->mprior = (odict *) (0);
	this->mafter = (odict *) (0);
	return;
}


/*====================================================================*
 *
 *   void ~odict()
 *
 *   delete all definitions in the symbol definition queue; delete
 *   the queue; delete any prior and after symbols; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

odict::~odict () 

{
	delete [] this->msymbol;
	delete [] this->mstring;
	delete this->mprior;
	delete this->mafter;
	return;
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

