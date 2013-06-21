/*====================================================================*
 *
 *   onode.hpp - interface for the onode classr;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oNODE_HEADER
#define oNODE_HEADER

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) onode: private otext 

{
public:
	onode ();
	onode (char const * name);
	virtual~ onode ();
	onode * node () const;
	char const * name () const;
	char const * text () const;
	void * data () const;
	onode & node (onode * node);
	onode & name (char const * name);
	onode & text (char const * text);
	onode & data (void * data);
	size_t order () const;
	size_t count () const;
	size_t level () const;
	signed value () const;
	onode & count (size_t count);
	onode & order (size_t order);
	onode & level (size_t level);
	onode & value (signed value);
	onode & clear ();
private:
	onode * mnode;
	char * mname;
	char * mtext;
	void * mdata;
	size_t mlevel;
	size_t mcount;
	size_t morder;
	signed mvalue;
};


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

