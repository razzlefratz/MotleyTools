/*====================================================================*
 *
 *   oitem.cpp - implementation of the oitem class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oITEM_SOURCE
#define oITEM_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oitem.hpp"

/*====================================================================*
 *
 *   char const *name() const;
 *
 *   return the string assigned to the mname member;
 *
 *--------------------------------------------------------------------*/

char const * oitem::name () const 

{
	return (this->mname);
}


/*====================================================================*
 *
 *   oitem & name(char const *string);
 *
 *   assign a new string to mname only when the new string is 
 *   different from the old string; 
 *
 *--------------------------------------------------------------------*/

oitem & oitem::name (char const * name) 

{
	this->mname = otext::replace (this->mname, name);
	return (* this);
}


/*====================================================================*
 *
 *   char const *text() const;
 *
 *   return the string assigned to the mtext member;
 *
 *--------------------------------------------------------------------*/

char const * oitem::text () const 

{
	return (this->mtext);
}


/*====================================================================*
 *
 *   oitem & text(char const * text);
 *
 *   assign a new string to mtext only when the new string is 
 *   different from the old string; 
 *
 *--------------------------------------------------------------------*/

oitem & oitem::text (char const * text) 

{
	this->mtext = otext::replace (this->mtext, text);
	return (* this);
}


/*====================================================================*
 *
 *   void * data() const;
 *
 *   return the pointer assigned to the mdata member;
 *
 *--------------------------------------------------------------------*/

void * oitem::data () const 

{
	return (this->mdata);
}


/*====================================================================*
 *
 *   oitem & data(void *data);
 *
 *   assign a new pointer to the mdata member;
 *
 *--------------------------------------------------------------------*/

oitem & oitem::data (void * data) 

{
	this->mdata = (void *) (data);
	return (* this);
}


/*====================================================================*
 *
 *   oitem * next() const;
 *
 *
 *--------------------------------------------------------------------*/

oitem * oitem::next () const 

{
	return (this->mitem);
}


/*====================================================================*
 *
 *   oitem & next(oitem * item);
 *
 *
 *--------------------------------------------------------------------*/

oitem & oitem::next (oitem * item) 

{
	this->mitem = item;
	return (* this);
}


/*====================================================================*
 *
 *   oitem & clear();
 *
 *
 *--------------------------------------------------------------------*/

oitem & oitem::clear () 

{
	this->mname = otext::replace (this->mname, "");
	this->mtext = otext::replace (this->mtext, "");
	this->mdata = (void *) (0);
	return (* this);
}


/*====================================================================*
 *
 *   oitem (char const *name, char const *text, void const *data);
 *   
 *   
 *--------------------------------------------------------------------*/

oitem::oitem (char const * name, char const * text, void const * data) 

{
	this->mname = otext::save (name);
	this->mtext = otext::save (text);
	this->mdata = (void *) (data);
	this->mitem = (oitem *) (0);
	return;
}


/*====================================================================*
 *
 *   oitem (char const *name, char const *text);
 *   
 *   
 *--------------------------------------------------------------------*/

oitem::oitem (char const * name, char const * text) 

{
	this->mname = otext::save (name);
	this->mtext = otext::save (text);
	this->mdata = (void *) (0);
	this->mitem = (oitem *) (0);
	return;
}


/*====================================================================*
 *
 *   oitem (char const *name, void const *data);
 *   
 *   
 *--------------------------------------------------------------------*/

oitem::oitem (char const * name, void const * data) 

{
	this->mname = otext::save (name);
	this->mtext = otext::save ("");
	this->mdata = (void *) (data);
	this->mitem = (oitem *) (0);
	return;
}


/*====================================================================*
 *
 *   oitem (char const *name);
 *   
 *   
 *--------------------------------------------------------------------*/

oitem::oitem (char const * name) 

{
	this->mname = otext::save (name);
	this->mtext = otext::save ("");
	this->mdata = (void *) (0);
	this->mitem = (oitem *) (0);
	return;
}


/*====================================================================*
 *
 *   oitem ();
 *   
 *   
 *--------------------------------------------------------------------*/

oitem::oitem () 

{
	this->mname = otext::save ("");
	this->mtext = otext::save ("");
	this->mdata = (void *) (0);
	this->mitem = (oitem *) (0);
	return;
}


/*====================================================================*
 *   
 *   ~oitem ();
 *   
 *   
 *--------------------------------------------------------------------*/

oitem::~oitem () 

{
	this->mdata = (void *) (0);
	delete [] this->mname;
	delete [] this->mtext;
	if (this->mitem != (oitem *) (0)) 
	{
		delete this->mitem;
	}
	return;
}


/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

