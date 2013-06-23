/*====================================================================*
 *
 *   oagenda.cpp - implementation of the oagenda class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oAGENDA_SOURCE
#define oAGENDA_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oagenda.hpp"

/*====================================================================*
 *
 *   unsigned oagenda::count() const;
 *
 *   return the number of items in the event queue;
 *
 *--------------------------------------------------------------------*/

unsigned oagenda::count () const 

{
	return (this->mheap->count ());
}

/*====================================================================*
 *
 *   char const *oagenda::event() const;
 *
 *   return the current event as a constant string;
 *
 *--------------------------------------------------------------------*/

char const * oagenda::event () const 

{
	oitem * item = this->mheap->item ();
	return (item != (oitem *) (0)? item->name (): (char *) (0));
}

/*====================================================================*
 *
 *   char const *oagenda::title() const;
 *
 *   return the current title as a constant string;
 *
 *--------------------------------------------------------------------*/

char const * oagenda::title () const 

{
	oitem * item = this->mheap->item ();
	return (item != (oitem *) (0)? item->text (): (char *) (0));
}

/*====================================================================*
 *
 *   oagenda & oagenda::insert(char const *event);
 *
 *   insert the event string into the queue at the proper position based 
 *   the event string value;
 *
 *--------------------------------------------------------------------*/

oagenda & oagenda::insert (char const * event) 

{
	this->mheap->insertitem (new oitem (event));
	return (* this);
}

/*====================================================================*
 *
 *   oagenda & oagenda::insert(char const *event, char const *title);
 *
 *   insert the event and title into the heap at the proper position based 
 *   on the event string value; 
 *
 *--------------------------------------------------------------------*/

oagenda & oagenda::insert (char const * event, char const * title) 

{
	this->mheap->insertitem (new oitem (event, title));
	return (* this);
}

/*====================================================================*
 *
 *   char const *oagenda::remove();
 *
 *   discard the current event; reorder the event queue; 
 *
 *--------------------------------------------------------------------*/

oagenda & oagenda::remove () 

{
	this->mheap->item ();
	return (* this);
}

/*====================================================================*
 *
 *   oagenda & oagenda::clear();
 *
 *   discard all agenda items;
 *
 *--------------------------------------------------------------------*/

oagenda & oagenda::clear () 

{
	this->mheap->clear ();
	return (* this);
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

oagenda::oagenda (signed order (char const *, char const *)) 

{
	this->mheap = new oheap (order);
	return;
}

oagenda::oagenda () 

{
	this->mheap = new oheap;
	return;
}

oagenda::~oagenda () 

{
	delete this->mheap;
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

