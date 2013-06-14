/*====================================================================*
 *
 *   onodes.cpp - implementation of the onodes class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oNODES_SOURCE
#define oNODES_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/onodes.hpp"

/*====================================================================*
 *
 *   size_t block () const;
 *
 *
 *--------------------------------------------------------------------*/

size_t onodes::block () const 

{
	return (this->mblock);
}


/*====================================================================*
 *
 *   size_t limit () const;
 *
 *
 *--------------------------------------------------------------------*/

size_t onodes::limit () const 

{
	return (this->mlimit);
}


/*====================================================================*
 *
 *   size_t count () const;
 *
 *
 *--------------------------------------------------------------------*/

size_t onodes::count () const 

{
	return (this->mcount);
}


/*====================================================================*
 *
 *   size_t index () const;
 *
 *
 *--------------------------------------------------------------------*/

size_t onodes::index () const 

{
	return (this->mindex);
}


/*====================================================================*
 *
 *   onodes & index (size_t index);
 *
 *
 *--------------------------------------------------------------------*/

onodes & onodes::index (size_t index) 

{
	this->mindex = index;
	return (* this);
}


/*====================================================================*
 *
 *   onodes & operator++ ();
 *
 *
 *--------------------------------------------------------------------*/

onodes & onodes::operator++ () 

{
	this->mindex++;
	return (* this);
}


/*====================================================================*
 *
 *   onode * operator[] (signed index) const;
 *
 *   return the onode pointer stored at the given mtable[] position; 
 *   return a void pointer if mtable[] is empty;
 *
 *--------------------------------------------------------------------*/

onode * onodes::operator [] (size_t index) const 

{
	return (index < this->mcount? this->mtable [index]: (onode *) (0));
}


/*====================================================================*
 *
 *   onode * onodes::node (size_t index) const
 *
 *   return the onode pointer stored at the given mtable[] position; 
 *   return a void pointer if mtable[] is empty;
 *
 *--------------------------------------------------------------------*/

onode * onodes::node (size_t index) const 

{
	return (index < this->mcount? this->mtable [index]: (onode *) (0));
}


/*====================================================================*
 *
 *   onode * node () const;
 *
 *   return the onode pointer stored at the given mtable[] position; 
 *   return a void pointer if mtable[] is empty;
 *
 *--------------------------------------------------------------------*/

onode * onodes::node () const 

{
	return (this->mindex < this->mcount? this->mtable [this->mindex]: (onode *) (0));
}


/*====================================================================*
 *
 *   onode * add (char const *nodename);
 *
 *   return the address of the named node; create the node if missing;
 *
 *--------------------------------------------------------------------*/

onodes & onodes::add (char const * nodename) 

{
	for (this->mindex = 0; this->mindex < this->mcount; this->mindex++) 
	{
		if (!std::strcmp (nodename, this->mtable [this->mindex] ->name ())) 
		{
			return (* this);
		}
	}
	if (this->mcount >= this->mlimit) 
	{
		onode ** ntable = this->mtable;
		this->mlimit = this->mlimit + this->mblock;
		this->mblock = this->mlimit - this->mblock;
		this->mtable = new onode * [this->mlimit];
		for (this->mindex = 0; this->mindex < this->mcount; this->mindex++) 
		{
			this->mtable [this->mindex] = ntable [this->mindex];
		}
		delete [] ntable;
	}
	this->mtable [this->mcount++] = new onode (nodename);
	return (* this);
}


/*====================================================================*
 *
 *   onodes & clear();
 *
 *
 *
 *--------------------------------------------------------------------*/

onodes & onodes::clear () 

{
	for (this->mindex = 0; this->mindex < this->mcount; this->mindex++) 
	{
		this->mentry = this->mtable [this->mindex];
		this->mtable [this->mindex] = (onode *) (0);
		delete this->mentry;
	}
	return (* this);
}


/*====================================================================*
 *
 *   onodes ();
 *
 *
 *--------------------------------------------------------------------*/

onodes::onodes () 

{
	this->mtable = new onode * [NODES_MAX];
	this->mlimit = this->mblock = NODES_MAX;
	this->mcount = this->mindex = 0;
	this->mentry = (onode *) (0);
	return;
}


/*====================================================================*
 *
 *   ~onodes ();
 *
 *
 *--------------------------------------------------------------------*/

onodes::~onodes () 

{
	this->mentry = (onode *) (0);
	delete [] this->mtable;
	return;
}


/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

