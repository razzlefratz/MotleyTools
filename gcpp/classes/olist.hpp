/*====================================================================*
 *
 *   olist.hpp - interface for the olist class;
 *
 *   this object imlements an ordered list engine for oitem objects; it
 *   is used by oroster, ocatalog and oglossary object classes to store,
 *   select and fetch information;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oLIST_HEADER
#define oLIST_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oitem.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) olist

{
public: 
	olist ();
	olist (int order (char const *, char const *));
	virtual ~ olist ();
	char const * title () const;
	olist & title (char const * title);
	oitem * operator [] (signed index) const;
	unsigned index () const;
	unsigned count () const;
	unsigned lower () const;
	unsigned upper () const;
	oitem * item () const;
	oitem * items (unsigned index) const;
	oitem * cycle (signed index) const;
	bool defined (char const * symbol);
	bool defined (char const * symbol, char const * string);
	unsigned indexof (char const * symbol);
	unsigned indexof (char const * symbol, char const * string);
	olist & select (char const * symbol);
	olist & select (char const * symbol, char const * string);
	oitem * item (char const * symbol);
	oitem * item (char const * symbol, char const * string);
	olist & insertitem (oitem * item);
	olist & removeitem ();
	olist & bound (char const * symbol);
	olist & clear ();
private: 
	char * mtitle;
	oitem ** mtable;
	signed (* morder) (char const *, char const *);
	unsigned mblock;
	unsigned mlimit;
	unsigned mstart;
	unsigned mindex;
	unsigned mcount;
	unsigned mlower;
	unsigned mupper;
};

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



