/*====================================================================*
 *
 *   oedge.cpp - implementation of the oedge class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oEDGE_SOURCE
#define oEDGE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oedge.hpp"

/*====================================================================*
 *
 *   oedge * oedge::source () const;
 *
 *
 *--------------------------------------------------------------------*/

onode * oedge::source () const 

{
	return (this->msource);
}

/*====================================================================*
 *
 *   onode * oedge::target  () const;
 *
 *
 *--------------------------------------------------------------------*/

onode * oedge::target () const 

{
	return (this->mtarget);
}

/*====================================================================*
 *
 *   signed oedge::value () const;
 *
 *
 *--------------------------------------------------------------------*/

signed oedge::value () const 

{
	return (this->mvalue);
}

/*====================================================================*
 *
 *   oedge & oedge::value (size_t count);
 *
 *
 *--------------------------------------------------------------------*/

oedge & oedge::value (signed value) 

{
	this->mvalue = value;
	return (* this);
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

oedge::oedge (onode * sourcenode, onode * targetnode) 

{
	this->msource = sourcenode;
	this->mtarget = targetnode;
	this->mvalue = 0;
	return;
}

oedge::~oedge () 

{
	delete this->msource;
	delete this->mtarget;
	this->mvalue = 0;
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

