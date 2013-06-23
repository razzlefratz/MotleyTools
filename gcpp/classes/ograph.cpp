/*====================================================================*
 *
 *   ograph.cpp - implementation of the ograph class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oGRAPH_SOURCE
#define oGRAPH_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ograph.hpp"
#include "../classes/oerror.hpp"

/*====================================================================*
 *
 *   char const *name () const;
 *
 *   return the object name string as a constant;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * ograph::name () 

{
	return (this->mname);
}

/*====================================================================*
 *
 *   ograph & name (char const *string);
 *
 *   assign a new string as the name only if the new string differs 
 *   from the old string; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ograph & ograph::name (char const * name) 

{
	this->mname = ograph::replace (this->mname, name);
	return (* this);
}

/*====================================================================*
 *
 *   onode * node () const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

onode * ograph::node () const 

{
	return (this->mnode);
}

/*====================================================================*
 *
 *   ograph & addnode (char const *nodename);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ograph & ograph::addnode (char const * nodename) 

{
	this->mnodes->add (nodename);
	return (* this);
}

/*====================================================================*
 *
 *   ograph & relate (char const *group, char const *member);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ograph & ograph::addedge (char const * needname, char const * feedname) 

{
	onode * neednode = this->mnodes->add (needname).node ();
	onode * feednode = this->mnodes->add (feedname).node ();
	this->medges->add (neednode, feednode);
	return (* this);
}

/*====================================================================*
 *
 *   ograph & populate (char colon, char comma, bool invert);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ograph & ograph::populate (char colon, char comma) 

{
	char one [oGRAPH_SYMBOL_LENGTH] = "";
	char two [oGRAPH_SYMBOL_LENGTH] = "";
	char * sp;
	int c;
	while ((c = std::cin.get ()) != EOF) 
	{
		for (sp = one; nobreak (c); c = std::cin.get ()) 
		{
			if ((char) (c) == colon) 
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
		for (sp = two; nobreak (c); c = std::cin.get ()) 
		{
			if ((char) (c) == comma) 
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
		if (ograph::anyset (oGRAPH_MODE_INVERT)) 
		{
			this->addedge (two, one);
		}
		else 
		{
			this->addedge (one, two);
		}
	}
	return (* this);
}

/*====================================================================*
 *   
 *   void discover();
 *
 *   search the node table and traverse each node to discover all
 *   starting points; traverse does not traverse nodes visited by
 *   prior traversal;
 *
 *   compute the width of numeric fields using successive division
 *   by ten; member morder should be zero on exit from this loop;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ograph & ograph::discover () 

{
	this->mcount = this->mnodes->count ();
	this->mwidth = 0;
	while (this->mcount > 0) 
	{
		this->mcount /= 10;
		this->mwidth++;
	}
	while (this->mcount < this->mnodes->count ()) 
	{
		ograph::traverse (this->mnodes->node (this->mcount++));
	}
	return (* this);
}

/*====================================================================*
 *   
 *   ograph & traverse (onode *node);
 *
 *   perform a depth-first search of the edge table starting from 
 *   the specified node; set the enter count before and the leave 
 *   count after the node is searched; ignore visited nodes; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ograph & ograph::traverse (onode * node) 

{

#ifdef CMASSOC_SAFEMODE

	if (!node) 
	{
		return (* this);
	}

#endif

/*
 * if this node is present in the open node stack then it is currently 
 * being analysed and forms a circular reference; 
 */

	for (onode * temp = this->mnode; temp; temp = temp->node ()) 
	{
		if (temp == node) 
		{
			std::cerr << node->name () << oGRAPH_TEXT_MORE;
			ograph::trace (this->mnode, node);
			std::cerr << node->name () << "\n";
			oerror::error (0, 0, "bailing out!");
			return (* this);
		}
	}

/*
 * if the level or order are non-zero then this node has already been 
 * traversed through another relationship; no need to traverse again;
 */

	if (node->level ()) 
	{
		return (* this);
	}
	if (node->order ()) 
	{
		return (* this);
	}
	node->node (this->mnode);
	this->mnode = node;
	for (size_t index = 0; index < this->medges->count (); index++) 
	{
		oedge * edge = this->medges->edge (index);
		if (edge->source () == node) 
		{
			ograph::traverse (edge->target ());
			if (node->level () < edge->target () ->level ()) 
			{
				node->level (edge->target () ->level ());
			}
		}
	}
	this->mnode = node->node ();
	node->node ((onode *) (0));
	node->order (++this->morder);
	if (ograph::anyset (oGRAPH_SHOW_LEVEL)) 
	{
		std::cout.width (this->mwidth);
		std::cout.fill ('0');
		std::cout << node->level () << " ";
	}
	if (ograph::anyset (oGRAPH_SHOW_ORDER)) 
	{
		std::cout.width (this->mwidth);
		std::cout.fill ('0');
		std::cout << node->order () << " ";
	}
	for (signed level = node->level (); level; level--) 
	{
		std::cout << "\t";
	}
	std::cout << node->name () << std::endl;
	node->level (node->level () + 1);
	return (* this);
}

/*====================================================================*
 * 
 *   ograph & trace(onode * temp, onode *node);
 *
 *   print circular reference chain by dumping the open node stack
 *   maintained by method traverse(); 
 *
 *--------------------------------------------------------------------*/

ograph & ograph::trace (onode * node, onode * stop) 

{
	if ((node) && (node != stop)) 
	{
		ograph::trace (node->node (), stop);
		std::cerr << node->name () << oGRAPH_TEXT_MORE;
	}
	return (* this);
}

/*====================================================================*
 * 
 *   ograph & clear ();
 *
 *   clear this node and subordinate names; 
 *
 *--------------------------------------------------------------------*/

ograph & ograph::clear () 

{
	this->medges->clear ();
	this->mnodes->clear ();
	this->mname = ograph::save ("");
	this->mnode = (onode *) (0);
	this->mcount = 0;
	this->morder = 0;
	this->mwidth = 0;
	return (* this);
}

/*====================================================================*
 * 
 *   ograph ()
 *
 *
 *--------------------------------------------------------------------*/

ograph::ograph () 

{
	this->medges = new oedges;
	this->mnodes = new onodes;
	this->mname = ograph::save ("");
	this->mnode = (onode *) (0);
	this->mcount = 0;
	this->morder = 0;
	this->mwidth = 0;
	return;
}

/*====================================================================*
 * 
 *   ~ograph ()
 *
 *
 *--------------------------------------------------------------------*/

ograph::~ograph () 

{
	delete [] this->mname;
	delete this->mnodes;
	delete this->medges;
	this->mnode = (onode *) (0);
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

