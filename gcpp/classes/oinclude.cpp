/*====================================================================*
 *
 *   oinclude.cpp - definition of oinclude class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oINCLUDE_SOURCE
#define oINCLUDE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>
#include <cctype>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oinclude.hpp"

/*====================================================================*
 *
 *   oinclude & state (void) const;
 *   
 *   return the tri-state switch value as -1, 0 or 1;
 *   
 *--------------------------------------------------------------------*/

signed oinclude::state (void) const 

{
	return (this->mstate);
}

/*====================================================================*
 *
 *   signed state(signed state);
 *   
 *   set the tri-state switch value to -1, 0 or 1;
 *   
 *--------------------------------------------------------------------*/

oinclude & oinclude::state (signed state) 

{
	if (state > 0) 
	{
		state = +1;
	}
	if (state < 0) 
	{
		state = -1;
	}
	this->mstate = state;
	return (* this);
}

/*====================================================================*
 *
 *   oinclude & filename (char const * string);
 *   
 *   set include guard title to the basename portion of the filename
 *   string; 
 *   
 *--------------------------------------------------------------------*/

oinclude & oinclude::filename (char const * string) 

{
	char buffer [FILENAME_MAX];
	char * sp = buffer;
	char const * cp;
	for (cp = string; * string; string++) 
	{
		if ((* string == '/') || (* string == '\\')) 
		{
			cp = string + 1;
		}
	}
	while ((* cp) && (* cp != '.')) 
	{
		* sp++ = std::toupper (* cp++);
	}
	* sp = (char) (0);
	this->title (buffer);
	return (* this);
}

/*====================================================================*
 *
 *   oinclude & title (void) const;
 *
 *   return include guard title string;
 *
 *--------------------------------------------------------------------*/

char const * oinclude::title (void) const 

{
	return (this->mtitle);
}

/*====================================================================*
 *
 *   oinclude & title (char const * title);
 *
 *   set include guard title if different from previous label;
 *
 *--------------------------------------------------------------------*/

oinclude & oinclude::title (char const * title) 

{
	this->mtitle = otext::replace (this->mtitle, title);
	return (* this);
}

/*====================================================================*
 *
 *   oinclude & label (void) const;
 *
 *   return include guard label string;
 *
 *--------------------------------------------------------------------*/

char const * oinclude::label (void) const 

{
	return (this->mclass);
}

/*====================================================================*
 *
 *   oinclude & label (char const * label);
 *
 *   set include guard label if different from previous label;
 *
 *--------------------------------------------------------------------*/

oinclude & oinclude::label (char const * label) 

{
	this->mclass = otext::replace (this->mclass, label);
	return (* this);
}

/*====================================================================*
 *
 *   oinclude & cheader (void);
 *
 *   insert an include guard plus one blank line if tri-state switch 
 *   mstate is positive then toggle the switch;
 *  
 *--------------------------------------------------------------------*/

oinclude & oinclude::header (void) 

{
	if (this->mstate > 0) 
	{
		this->mstate = -this->mstate;
		std::cout << "#ifndef " << this->mtitle << "_" << this->mclass << std::endl;
		std::cout << "#define " << this->mtitle << "_" << this->mclass << std::endl;
		std::cout << std::endl;
	}
	return (* this);
}

/*====================================================================*
 *
 *   oinclude & footer (void);
 *
 *   terminate inlude gurard plus one blank line if tri-state switch
 *   mstate is negative then toggle the switch;
 *
 *--------------------------------------------------------------------*/

oinclude & oinclude::footer (void) 

{
	if (this->mstate < 0) 
	{
		this->mstate = -this->mstate;
		std::cout << "#endif" << std::endl;
		std::cout << std::endl;
	}
	return (* this);
}

/*====================================================================*
 *
 *   oinclude (char const * title, char const * label);
 *
 *--------------------------------------------------------------------*/

oinclude::oinclude (char const * title, char const * label) 

{
	this->mtitle = oinclude::save (title);
	this->mclass = oinclude::save (label);
	this->mstate = 0;
	return;
}

/*====================================================================*
 *
 *   oinclude (void)
 *
 *--------------------------------------------------------------------*/

oinclude::oinclude () 

{
	this->mtitle = oinclude::save ("MODULE");
	this->mclass = oinclude::save ("SOURCE");
	this->mstate = 0;
	return;
}

/*====================================================================*
 *
 *   ~oinclude (void)
 *
 *--------------------------------------------------------------------*/

oinclude::~oinclude (void) 

{
	delete [] this->mtitle;
	delete [] this->mclass;
	return;
}

/*====================================================================*
 *   end definition
 *--------------------------------------------------------------------*/

#endif

