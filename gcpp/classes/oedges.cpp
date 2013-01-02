/*====================================================================*
 *
 *   oedges.cpp - implementation of the oedges class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oEDGES_SOURCE
#define oEDGES_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oedges.hpp"

/*====================================================================*
 *
 *   size_t block () const;
 *
 *
 *--------------------------------------------------------------------*/

size_t oedges::block () const 

{
	return (this->mblock);
}


/*====================================================================*
 *
 *   size_t limit () const;
 *
 *
 *--------------------------------------------------------------------*/

size_t oedges::limit () const 

{
	return (this->mlimit);
}


/*====================================================================*
 *
 *   size_t count () const;
 *
 *
 *--------------------------------------------------------------------*/

size_t oedges::count () const 

{
	return (this->mcount);
}


/*====================================================================*
 *
 *   size_t index () const;
 *
 *
 *--------------------------------------------------------------------*/

size_t oedges::index () const 

{
	return (this->mindex);
}


/*====================================================================*
 *
 *   oedge * operator [] (size_t index) const;
 *
 *   return the oedge pointer at the given mtable [] position or void 
 *   if index is out of range; 
 *
 *--------------------------------------------------------------------*/

oedge * oedges::operator [] (size_t index) const 

{
	return (index < this->mcount? this->mtable [index]: (oedge *) (0));
}


/*====================================================================*
 *
 *   oedge * edge (size_t index) const
 *
 *   return the oedge pointer at the given mtable position or void 
 *   if index is out of range; 
 *
 *--------------------------------------------------------------------*/

oedge * oedges::edge (size_t index) const 

{
	return (index < this->mcount? this->mtable [index]: (oedge *) (0));
}


/*====================================================================*
 *
 *   oedge * edge () const
 *
 *   return the oedge pointer at the given mtable position or void 
 *   if index is out of range; 
 *
 *--------------------------------------------------------------------*/

oedge * oedges::edge () const 

{
	return (this->mindex < this->mcount? this->mtable [this->mindex]: (oedge *) (0));
}


/*====================================================================*
 *
 *   oedge * add (onode *sourcenode, onode *targetnode);
 *
 *   create a new edge, if missing, and return the edge address; 
 *
 *--------------------------------------------------------------------*/

oedges & oedges::add (onode *sourcenode, onode *targetnode) 

{
	for (this->mindex = 0; this->mindex < this->mcount; this->mindex++) 
	{
		if (this->mtable [this->mindex] ->source () == sourcenode) 
		{
			if (this->mtable [this->mindex] ->target () == targetnode) 
			{
				return (*this);
			}
		}
	}
	if (this->mcount > this->mlimit) 
	{
		oedge ** ntable = this->mtable;
		this->mlimit = this->mlimit + this->mblock;
		this->mblock = this->mlimit - this->mblock;
		this->mtable = new oedge * [this->mlimit];
		for (this->mindex = 0; this->mindex < this->mcount; this->mindex++) 
		{
			this->mtable [this->mindex] = ntable [this->mindex];
		}
		delete [] ntable;
	}
	this->mtable [this->mcount++] = new oedge (sourcenode, targetnode);
	return (*this);
}


/*====================================================================*
 *
 *   oedges & clear();
 *
 *
 *
 *--------------------------------------------------------------------*/

oedges & oedges::clear () 

{
	for (this->mindex = 0; this->mindex < this->mcount; this->mindex++) 
	{
		this->medge = this->mtable [this->mindex];
		this->mtable [this->mindex] = (oedge *) (0);
		delete this->medge;
	}
	this->mcount = this->mindex = 0;
	return (*this);
}


/*====================================================================*
 *
 *   oedges ();
 *
 *
 *
 *--------------------------------------------------------------------*/

oedges::oedges () 

{
	this->mtable = new oedge * [EDGE_MAX];
	this->mlimit = this->mblock = EDGE_MAX;
	this->mcount = this->mindex = 0;
	return;
}


/*====================================================================*
 *
 *   ~oedges ();
 *
 *
 *
 *--------------------------------------------------------------------*/

oedges::~ oedges () 

{
	this->medge = (oedge *) (0);
	delete [] this->mtable;
	return;
}


/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

