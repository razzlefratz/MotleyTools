/*====================================================================*
 *
 *   odocument.cpp - implementation of the odocument class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oDOCUMENT_SOURCE
#define oDOCUMENT_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <cstring>
#include <ctime>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/odocument.hpp"

/*====================================================================*
 * 
 *   char const *odocument::title() const;
 *
 *   return the page title as a string constant;
 *
 *--------------------------------------------------------------------*/

char const * odocument::title() const

{
	return (this->root->title());
}

/*====================================================================*
 * 
 *   odocument & odocument::title(char const *title) 
 *
 *   replace the current title with the string argument if they differ;
 *
 *--------------------------------------------------------------------*/

odocument & odocument::title(char const * title)

{
	this->root->title(title);
	return (* this);
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

odocument::odocument()

{
	this->root = new otree();
	return;
}

odocument::odocument(char const * title)

{
	this->root = new otree(title);
	return;
}

odocument::~ odocument()

{
	delete [] this->mtitle;
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif



