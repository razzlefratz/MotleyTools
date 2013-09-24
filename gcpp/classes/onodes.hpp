/*====================================================================*
 *
 *   onodes.hpp - interface for the onodes classr;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oNODES_HEADER
#define oNODES_HEADER

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/onode.hpp"

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define NODES_MAX 100

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec(dllexport) onodes

{
public: 
	onodes ();
	virtual ~ onodes();
	size_t block() const;
	size_t limit() const;
	size_t count() const;
	size_t index() const;
	onodes & operator++ ();
	onodes & index(size_t index);
	onodes & add(char const * nodename);
	onode * operator[](size_t index) const;
	onode * node(size_t index) const;
	onode * node() const;
	onodes & organize(onode * node);
	onodes & clear();
private: 
	onode ** mtable;
	onode * mentry;
	size_t mblock;
	size_t mlimit;
	size_t mcount;
	size_t mindex;
};

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



