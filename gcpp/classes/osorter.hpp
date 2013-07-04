/*====================================================================*
 *
 *   osorter.hpp - interface for the osorter class.
 *
 *   This object maintains an ordered and unique list of character strings. Strings 
 *   assume proper order as their are added. Duplicates are automatically rejected.
 *   Additional memory is automatically allocated on list overflow. Insertion time
 *   increases as the list grows but retrieval time increases at a much slower rate.
 * 
 *   Strings are added with the insert() method which returns true when a string is
 *   actually inserted. Duplicates are quickly detected and rejected.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSORTER_HEADER
#define oSORTER_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

class __declspec (dllexport) osorter 

{
public:
	osorter ();
	osorter (int order (char const *, char const *));
	virtual ~ osorter ();
	unsigned index () const;
	unsigned start () const;
	unsigned count () const;
	bool insert (char const * string);
	bool remove (char const * string);
	void operator ++ ();
	bool operator += (char const * string);
	bool operator -= (char const * string);
	char const * string ();
	char const * strings (unsigned index);
	char const * operator [] (unsigned index);
	unsigned indexof (char const * string);
	bool defined (char const * string);
	osorter & define (char string [], unsigned char c);
	osorter & clear ();
	void home ();
	bool more ();
	void next ();
private:
	osorter & store (char const * string);
	char const ** mtable;

/* the table */

	signed (* morder) (char const *, char const *);
	unsigned mblock;

/* table allocation block size */

	unsigned mlimit;

/* table upper bound after each allocation */

	unsigned mstart;
	unsigned mlower;

/*   lower bound for binary search */

	unsigned mindex;

/*   table index */

	unsigned mupper;

/*   upper bound for binary search */

	unsigned mcount;

/* number of table entries */

};

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

