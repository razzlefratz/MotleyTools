/*====================================================================*
 *
 *   onode.cpp - implementation of the onode class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oNODE_SOURCE
#define oNODE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/onode.hpp"

/*====================================================================*
 *
 *   onode * node () const;
 *
 *   return the string assigned to the mnode member;
 *
 *--------------------------------------------------------------------*/

onode * onode::node () const 

{
	return (this->mnode);
}


/*====================================================================*
 *
 *   onode & node (onode * node);
 *
 *   assign a new string to the mnode member only when the new string is 
 *   different from the old string; 
 *
 *--------------------------------------------------------------------*/

onode & onode::node (onode * node) 

{
	this->mnode = node;
	return (* this);
}


/*====================================================================*
 *
 *   char const *name () const;
 *
 *   return the string assigned to the mname member;
 *
 *--------------------------------------------------------------------*/

char const * onode::name () const 

{
	return (this->mname);
}


/*====================================================================*
 *
 *   onode & name (char const * name);
 *
 *   assign a new string to the mname member only when the new string is 
 *   different from the old string; 
 *
 *--------------------------------------------------------------------*/

onode & onode::name (char const * name) 

{
	this->mname = otext::replace (this->mname, name);
	return (* this);
}


/*====================================================================*
 *
 *   char const *text () const;
 *
 *   return the string assigned to the mtext member;
 *
 *--------------------------------------------------------------------*/

char const * onode::text () const 

{
	return (this->mtext);
}


/*====================================================================*
 *
 *   onode & text (char const * text);
 *
 *   assign a new string to the mtext member only when the new string is 
 *   different from the old string; 
 *
 *--------------------------------------------------------------------*/

onode & onode::text (char const * text) 

{
	this->mtext = otext::replace (this->mtext, text);
	return (* this);
}


/*====================================================================*
 *
 *   void *data () const;
 *
 *   get the mdata pointer property;
 *
 *--------------------------------------------------------------------*/

void * onode::data () const 

{
	return (this->mdata);
}


/*====================================================================*
 *
 *   onode & data (void const *data);
 *
 *   assign a new value to the mdata pointer property; 
 *
 *--------------------------------------------------------------------*/

onode & onode::data (void * data) 

{
	this->mdata = data;
	return (* this);
}


/*====================================================================*
 *
 *   size_t count () const;
 *
 *
 *--------------------------------------------------------------------*/

size_t onode::count () const 

{
	return (this->mcount);
}


/*====================================================================*
 *
 *   onode & count (size_t count);
 *
 *
 *--------------------------------------------------------------------*/

onode & onode::count (size_t count) 

{
	this->mcount = count;
	return (* this);
}


/*====================================================================*
 *
 *   size_t order () const;
 *
 *
 *--------------------------------------------------------------------*/

size_t onode::order () const 

{
	return (this->morder);
}


/*====================================================================*
 *
 *   onode & order (size_t order);
 *
 *
 *--------------------------------------------------------------------*/

onode & onode::order (size_t order) 

{
	this->morder = order;
	return (* this);
}


/*====================================================================*
 *
 *   size_t level () const;
 *
 *
 *--------------------------------------------------------------------*/

size_t onode::level () const 

{
	return (this->mlevel);
}


/*====================================================================*
 *
 *   onode & level (size_t level);
 *
 *
 *--------------------------------------------------------------------*/

onode & onode::level (size_t level) 

{
	this->mlevel = level;
	return (* this);
}


/*====================================================================*
 *
 *   size_t value () const;
 *
 *
 *--------------------------------------------------------------------*/

signed onode::value () const 

{
	return (this->mvalue);
}


/*====================================================================*
 *
 *   onode & value (signed value);
 *
 *
 *--------------------------------------------------------------------*/

onode & onode::value (signed value) 

{
	this->mvalue = value;
	return (* this);
}


/*====================================================================*
 *
 *   onode & clear ();
 *
 *
 *--------------------------------------------------------------------*/

onode & onode::clear () 

{
	this->mlevel = 0;
	this->mcount = 0;
	this->morder = 0;
	this->mvalue = 0;
	return (* this);
}


/*====================================================================*
 *
 *   onode (char const *name)
 *
 *   
 *--------------------------------------------------------------------*/

onode::onode (char const * name) 

{
	this->mnode = (onode *) (0);
	this->mname = otext::save (name);
	this->mtext = otext::save ("");
	this->mdata = (void *) (0);
	this->mlevel = 0;
	this->mcount = 0;
	this->morder = 0;
	this->mvalue = 0;
	return;
}


/*====================================================================*
 *
 *   onode ()
 *
 *   
 *--------------------------------------------------------------------*/

onode::onode () 

{
	this->mnode = (onode *) (0);
	this->mname = otext::save ("");
	this->mtext = otext::save ("");
	this->mdata = (void *) (0);
	this->mlevel = 0;
	this->mcount = 0;
	this->morder = 0;
	this->mvalue = 0;
	return;
}


/*====================================================================*
 *
 *   ~onode ()
 *
 *   
 *--------------------------------------------------------------------*/

onode::~onode () 

{
	this->mnode = (onode *) (0);
	delete [] this->mname;
	delete [] this->mtext;
	this->mdata = (void *) (0);
	return;
}


/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

