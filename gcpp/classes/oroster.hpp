/*====================================================================*
 *
 *   oroster.hpp - interface for the oHeap class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oROSTER_HEADER
#define oROSTER_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstddef>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/olist.hpp"

/*====================================================================*
 *7
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oroster

{
public: 
	oroster ();
	oroster (signed order (char const *, char const *));
	virtual ~ oroster ();
	char const * title () const;
	oroster & title (char const * title);
	char const * symbol () const;
	char const * symbols (size_t index) const;
	unsigned int index () const;
	unsigned int count () const;
	bool defined (char const * symbol);
	unsigned indexof (char const * symbol);
	char const * operator [] (signed index) const;
	bool operator += (char const * symbol);
	bool operator -= (char const * symbol);
	bool insert (char const * symbol);
	bool remove (char const * symbol);
	oroster & clear ();
private: 
	olist * mlist;
};

/*====================================================================*
 *   end class declaration
 *--------------------------------------------------------------------*/

#endif



