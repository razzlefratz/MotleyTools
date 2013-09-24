/*====================================================================*
 *
 *   otodo.hpp - interface for the otodo class;
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

#ifndef oTODO_HEADER
#define oTODO_HEADER

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oitem.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec(dllexport) otodo

{
public: 
	otodo ();
	otodo (int order(char const *, char const *));
	virtual ~ otodo();
	char const * title() const;
	otodo & title(char const * string);
	size_t index() const;
	size_t start() const;
	size_t count() const;
	size_t limit() const;
	size_t block() const;
	oitem * operator[](size_t index) const;
	oitem * item() const;
	oitem * items(size_t index) const;
	bool defined(char const * symbol);
	size_t indexof(char const * symbol);
	otodo & select(char const * symbol);
	oitem * item(char const * symbol);
	otodo & insertitem(oitem * item);
	otodo & appenditem(oitem * item);
	otodo & removeitem();
	otodo & orderlist();
	otodo & clearlist();
private: 
	char * mtitle;
	oitem ** mtable;
	size_t mblock;

/* table allocation block size */

	size_t mlimit;

/* table upper bound after each allocation */

	size_t mstart;
	size_t mindex;

/*   table index */

	size_t mcount;

/* number of table entries */

};

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



