/*====================================================================*
 *
 *   ooutline.hpp - interface for the ooutline class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oOUTLINE_HEADER
#define oOUTLINE_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/otree.hpp"

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

#define UNDER_NODE (1 << 0)
#define FIRST_NODE (1 << 1)
#define FINAL_NODE (1 << 2)
#define ABOVE_NODE (1 << 3)
#define PRIOR_NODE (1 << 4)
#define AFTER_NODE (1 << 5)
#define BELOW_NODE (1 << 6)

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ooutline 

{
public:
	ooutline (char const * symbol);
	virtual ~ ooutline ();
	char const *title () const;
	char const *string () const;
	void *object () const;
	otree *tree () const;
	otree *nodes (long index) const;
	otree *insert (long index, unsigned order, char const * symbol);
	long first () const;
	long final () const;
	long count () const;
	ooutline & string (char * string);
	ooutline & object (void * object);
	char const *strings (long index) const;
	void *objects (long index) const;
	ooutline & clear ();
private:
	otree * mtree;
};


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

