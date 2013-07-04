/*====================================================================*
 *
 *   oedges.hpp - interface for the oedges classr;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oEDGES_HEADER
#define oEDGES_HEADER

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oedge.hpp"

#define EDGE_MAX 100

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oedges 

{
public:
	oedges ();
	virtual ~ oedges ();
	size_t block () const;
	size_t limit () const;
	size_t count () const;
	size_t index () const;
	oedges & add (onode * sourcenode, onode * targetnode);
	oedge * operator [] (size_t index) const;
	oedge * edge (size_t index) const;
	oedge * edge () const;
	oedges & clear ();
private:
	onode * mnode;
	oedge * medge;
	oedge ** mtable;
	size_t mblock;
	size_t mlimit;
	size_t mcount;
	size_t mindex;
};

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

