/*====================================================================*
 *
 *   oitem.hpp - interface for the oitem classr;
 *
 *   this object implements a generic means of storing information by
 *   name and classification; it is used by the olist, oheap, oroster,
 *   oglossary and ocatalog oject classes;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oITEM_HEADER
#define oITEM_HEADER

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oitem: private otext

{
public: 
	oitem ();
	oitem (char const * name);
	oitem (char const * name, void const * data);
	oitem (char const * name, char const * text);
	oitem (char const * name, char const * text, void const * data);
	virtual ~ oitem ();
	char const * name () const;
	char const * text () const;
	void * data () const;
	oitem & name (char const * string);
	oitem & text (char const * string);
	oitem & data (void * object);
	oitem * next () const;
	oitem & next (oitem * item);
	oitem & clear ();
private: 
	oitem * mitem;
	char * mname;
	char * mtext;
	void * mdata;
};

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif



