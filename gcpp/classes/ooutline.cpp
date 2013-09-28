/*====================================================================*
 *
 *   ooutline.cpp - implementation of the ooutline class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oOUTLINE_SOURCE
#define oOUTLINE_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ooutline.hpp"

/*====================================================================*
 *
 *   char const *title() const;
 *
 *
 *
 *--------------------------------------------------------------------*/

char const * ooutline::title () const

{
	return (this->mtree->nodename ());
}

/*====================================================================*
 *
 *   char const *string() const;
 *
 *
 *
 *--------------------------------------------------------------------*/

char const * ooutline::string () const

{
	return (this->mtree->nodetext ());
}

/*====================================================================*
 *
 *   void *object() const;
 *
 *
 *
 *--------------------------------------------------------------------*/

void * ooutline::object () const

{
	return (this->mtree->nodedata ());
}

/*====================================================================*
 *
 *   long first() const;
 *
 *
 *
 *--------------------------------------------------------------------*/

long ooutline::first () const

{
	return (this->mtree->first ());
}

/*====================================================================*
 *
 *   long final() const;
 *
 *
 *
 *--------------------------------------------------------------------*/

long ooutline::final () const

{
	return (this->mtree->final ());
}

/*====================================================================*
 *
 *   long count() const;
 *
 *
 *
 *--------------------------------------------------------------------*/

long ooutline::count () const

{
	return (this->mtree->count ());
}

/*====================================================================*
 *
 *   otree *tree() const;
 *
 *
 *
 *--------------------------------------------------------------------*/

otree * ooutline::tree () const

{
	return (this->mtree);
}

/*====================================================================*
 *
 *   otree *nodes(long index) const;
 *
 *
 *
 *--------------------------------------------------------------------*/

otree * ooutline::nodes (long index) const

{
	return (this->mtree->nodes (index));
}

/*====================================================================*
 *
 *   char const *strings(long index) const;
 *
 *
 *
 *--------------------------------------------------------------------*/

char const * ooutline::strings (long index) const

{
	return (this->mtree->strings (index));
}

/*====================================================================*
 *
 *   void *objects(long index) const;
 *
 *
 *
 *--------------------------------------------------------------------*/

void * ooutline::objects (long index) const

{
	return (this->mtree->objects (index));
}

/*====================================================================*
 *
 *   ooutline & object (void * object);
 *
 *
 *
 *--------------------------------------------------------------------*/

ooutline & ooutline::object (void * object)

{
	this->mtree->nodedata (object);
	return (* this);
}

/*====================================================================*
 *
 *   otree * insert(long index, unsigned order, char const * symbol);
 *
 *
 *
 *--------------------------------------------------------------------*/

otree * ooutline::insert (long index, unsigned order, char const * symbol)

{
	otree * node = this->mtree->nodes (index);
	if (node)
	{
		switch (order)
		{
		case ABOVE_NODE:
			node = node->insertabove (symbol);
			break;
		case BELOW_NODE:
			node = node->insertbelow (symbol);
			break;
		case PRIOR_NODE:
			node = node->insertprior (symbol);
			break;
		case AFTER_NODE:
			node = node->insertafter (symbol);
			break;
		case FIRST_NODE:
			node = node->appendprior (symbol);
			break;
		case FINAL_NODE:
			node = node->appendafter (symbol);
			break;
		case UNDER_NODE:
			node = node->appendbelow (symbol);
			break;
		default: 
			node = (otree *) (0);
			break;
		}
		this->mtree->reorder (0, 0);
	}
	return (node);
}

/*====================================================================*
 *
 *   ooutline & clear ()
 *
 *
 *--------------------------------------------------------------------*/

ooutline & ooutline::clear ()

{
	delete this->mtree;
	return (* this);
}

/*====================================================================*
 *
 *   ooutline (char const *symbol);
 *
 *
 *--------------------------------------------------------------------*/

ooutline::ooutline (char const * symbol)

{
	this->mtree = new otree (symbol);
}

/*====================================================================*
 *
 *   ~ooutline ();
 *
 *
 *--------------------------------------------------------------------*/

ooutline::~ ooutline ()

{
	delete this->mtree;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



