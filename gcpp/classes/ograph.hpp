/*====================================================================*
 *
 *   ograph.hpp - interface for the ograph class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oGRAPH_HEADER
#define oGRAPH_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oqueue.hpp"
#include "../classes/onodes.hpp"
#include "../classes/oedges.hpp"
#include "../classes/oflagword.hpp"
#include "../classes/oascii.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *   class constants;
 *--------------------------------------------------------------------*/

#define oGRAPH_MODE_INVERT (1 << 0)
#define oGRAPH_SHOW_SYMBOL (1 << 1)
#define oGRAPH_SHOW_STRUCT (1 << 2)
#define oGRAPH_SHOW_ORDER (1 << 3)
#define oGRAPH_SHOW_LEVEL (1 << 4)

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec(dllexport) ograph: private otext, private oascii, public oflagword

{
public: 
	ograph (void);
	virtual ~ ograph(void);
	char const * name(void);
	onode * node(void) const;
	ograph & name(char const * name);
	ograph & addnode(char const * nodename);
	ograph & addedge(char const * rootname, char const * nodename);
	ograph & populate(char colon, char comma);
	ograph & discover(void);
	ograph & trace(onode * node, onode * stop);
	ograph & print(signed indent);
	ograph & clear(void);
private: 
	ograph & traverse(onode * node);
	char * mname;
	onodes * mnodes;
	oedges * medges;
	onode * mnode;
	size_t morder;
	size_t mcount;
	size_t mwidth;
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif



