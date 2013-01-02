/*====================================================================*
 *
 *   osymbol.cpp - implementation of the osymbol class.
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

#ifndef oSYMBOL_SOURCE
#define oSYMBOL_SOURCE

/*====================================================================*
 *   system header files; 
 *--------------------------------------------------------------------*/

#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../classes/osymbol.hpp"

/*====================================================================*
 *
 *   osymbol & define (char const *symbol, char const *string);
 *
 *   define symbol as string; create symbol if missing or redefine
 *   symbol if already present; return the object address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osymbol & osymbol::define (char const *symbol, char const *string) 

{
	osymbol * node = this;
	if (symbol) while (node) 
	{
		signed order = std::strcmp (symbol, (char *) (node->mqueue->data ()));
		if (order < 0) 
		{
			if (!node->mprior) 
			{
				node->mprior = new osymbol (symbol);
			}
			node = node->mprior;
			continue;
		}
		if (order > 0) 
		{
			if (!node->mafter) 
			{
				node->mafter = new osymbol (symbol);
			}
			node = node->mafter;
			continue;
		}
		node->mqueue->insert (otext::save (string));
		break;
	}
	return (*this);
}


/*====================================================================*
 *  
 *   bool defined (char const *symbol) const;
 *
 *   return true if symbol is present and currently defined;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool osymbol::defined (char const *symbol) const 

{
	const osymbol *node = osymbol::node (symbol);
	if (node) 
	{
		return (!node->mqueue->empty ());
	}
	return (false);
}


/*====================================================================*
 *  
 *   char const *lookup (char const *symbol) const;
 *
 *   return the current symbol definition, if one exists, or NULL 
 *   if undefined;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const *osymbol::lookup (char const *symbol) const 

{
	const osymbol *node = osymbol::node (symbol);
	if (node) 
	{
		return ((char const *) (node->mqueue->head () ->data ()));
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

char const *osymbol::expand (char const *symbol) const 

{
	const osymbol *node = osymbol::node (symbol);
	if (node) 
	{
		return ((char const *) (node->mqueue->head () ->data ()));
	}
	return (symbol);
}


/*====================================================================*
 *
 *   osymbol & revert (char const *symbol);
 *
 *   delete the current symbol definition (if one exists) and return
 *   the object address;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osymbol & osymbol::revert (char const *symbol) 

{
	const osymbol *node = osymbol::node (symbol);
	if (node) if (!node->mqueue->empty ()) 
	{
		delete (char *) (node->mqueue->head () ->data ());
		node->mqueue->remove ();
	}
	return (*this);
}


/*====================================================================*
 *
 *   osymbol * node (char const *symbol);
 *
 *   find symbol in the table using an inorder search; return the
 *   symbol node address if present or a null address if missing;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

const osymbol * osymbol::node (char const *symbol) const 

{
	const osymbol * node = this;
	if (symbol) while (node) 
	{
		signed order = std::strcmp (symbol, (char *) (node->mqueue->data ()));
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
		return (node);
	}
	return ((osymbol *)(0));
}


/*====================================================================*
 *
 *   osymbol & print ();
 *
 *   enumerate symbols and definition history on stderr;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osymbol & osymbol::enumerate () 

{
	if (this->mprior) 
	{
		this->mprior->enumerate ();
	}
	this->print ();
	if (this->mafter) 
	{
		this->mafter->enumerate ();
	}
	return (*this);
}


/*====================================================================*
 *
 *   osymbol & print ();
 *
 *   print definition history for current node;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osymbol & osymbol::print () 

{
	std::cerr << "symbol:[" << (char const *) (this->mqueue->data ()) << "]" << std::endl;
	for (oqueue * mentry = mqueue->head (); mentry != this->mqueue; mentry = mentry->head ()) 
	{
		std::cerr << "\tstring:[" << (char const *) (mentry->data ()) << "]" << std::endl;
	}
	return (*this);
}


/*====================================================================*
 *
 *   osymbol & clear ();
 *
 *   clear the symbol table for reuse;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osymbol & osymbol::clear () 

{
	while (!this->mqueue->empty ()) 
	{
		delete (char *) (this->mqueue->head () ->data ());
		this->mqueue->remove ();
	}
	delete this->mprior;
	delete this->mafter;
	this->mprior = (osymbol *) (0);
	this->mafter = (osymbol *) (0);
	return (*this);
}


/*====================================================================*
 *
 *  void  osymbol (char const * symbol);
 *
 *   initialize this symbol with an empty symbol name and definition
 *   string; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osymbol::osymbol (char const * symbol) 

{
	this->mqueue = new oqueue (otext::save (symbol));
	this->mprior = (osymbol *) (0);
	this->mafter = (osymbol *) (0);
	return;
}


/*====================================================================*
 *
 *   void osymbol (char const * symbol, char const * string);
 *
 *   initialize this symbol with the given symbol name and string 
 *   definition;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osymbol::osymbol (char const * symbol, char const * string) 

{
	this->mqueue = new oqueue (otext::save (symbol));
	this->mqueue->insert (otext::save (string));
	this->mprior = (osymbol *) (0);
	this->mafter = (osymbol *) (0);
	return;
}


/*====================================================================*
 *
 *   void ~osymbol()
 *
 *   delete definitions from definition stack for each symbol then
 *   delete the stack then delete the symbol node;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osymbol::~osymbol () 

{
	while (!this->mqueue->empty ()) 
	{
		delete (char *) (this->mqueue->head () ->data ());
		this->mqueue->remove ();
	}
	delete (char *) (this->mqueue->data ());
	delete this->mprior;
	delete this->mafter;
	delete this->mqueue;
	return;
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

