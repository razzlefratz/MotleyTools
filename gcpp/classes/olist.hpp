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
	char const *title () const;
	olist & title (char const *title);
	oitem *operator [] (signed index) const;
	size_t index () const;
	size_t count () const;
	size_t lower () const;
	size_t upper () const;
	oitem *item () const;
	oitem *items (size_t index) const;
	oitem *cycle (signed index) const;
	bool defined (char const *symbol);
	bool defined (char const *symbol, char const *string);
	size_t indexof (char const *symbol);
	size_t indexof (char const *symbol, char const *string);
	olist & select (char const *symbol);
	olist & select (char const *symbol, char const *string);
	oitem *item (char const *symbol);
	oitem *item (char const *symbol, char const *string);
	olist & insertitem (oitem * item);
	olist & removeitem ();
	olist & bound (char const *symbol);
	olist & clear ();
private:
	char *mtitle;
	oitem **mtable;
	signed (*morder) (char const *, char const *);
	size_t mblock;
	size_t mlimit;
	size_t mstart;
	size_t mindex;
	size_t mcount;
	size_t mlower;
	size_t mupper;
};


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

