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
#include <cstring>
#include <cstdio>
#include <cctype>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oinclude.hpp"

/*====================================================================*
 *
 *   oinclude & state() const;
 *   
 *   return the tri-state switch value as -1, 0 or 1;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed oinclude::state () const 

{
	return (this->mstate);
}


/*====================================================================*
 *
 *   signed state(signed state);
 *   
 *   set the tri-state switch value to -1, 0 or 1;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
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
	return (*this);
}


/*====================================================================*
 *
 *   oinclude & filename (char const *string);
 *   
 *   set include guard title to the basename portion of the filename
 *   string; 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oinclude & oinclude::filename (char const *string) 

{
	char buffer [FILENAME_MAX];
	char *sp = buffer;
	char const *cp;
	for (cp = string; *string; string++) 
	{
		if ((*string == '/') || (*string == '\\')) 
		{
			cp = string + 1;
		}
	}
	while ((*cp) && (*cp != '.')) 
	{
		*sp++ = toupper (*cp++);
	}
	*sp = (char) (0);
	this->title (buffer);
	return (*this);
}


/*====================================================================*
 *
 *   oinclude & title () const;
 *
 *   return include guard title string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * oinclude::title () const 

{
	return (this->mtitle);
}


/*====================================================================*
 *
 *   oinclude & title (char const *title);
 *
 *   set include guard title if different from previous label;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oinclude & oinclude::title (char const *title) 

{
	this->mtitle = oinclude::replace (this->mtitle, title);
	return (*this);
}


/*====================================================================*
 *
 *   oinclude & label () const;
 *
 *   return include guard label string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * oinclude::label () const 

{
	return (this->mclass);
}


/*====================================================================*
 *
 *   oinclude & label (char const *label);
 *
 *   set include guard label if different from previous label;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oinclude & oinclude::label (char const *label) 

{
	this->mclass = oinclude::replace (this->mclass, label);
	return (*this);
}


/*====================================================================*
 *
 *   oinclude & cheader ();
 *
 *   insert an include guard plus one blank line if tri-state switch 
 *   mstate is positive then toggle the switch;
 *  
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oinclude & oinclude::header () 

{
	if (this->mstate > 0) 
	{
		this->mstate = -this->mstate;
		std::cout << "#ifndef " << this->mtitle << "_" << this->mclass << std::endl;
		std::cout << "#define " << this->mtitle << "_" << this->mclass << std::endl;
		std::cout << std::endl;
	}
	return (*this);
}


/*====================================================================*
 *
 *   oinclude & footer ();
 *
 *   terminate inlude gurard plus one blank line if tri-state switch
 *   mstate is negative then toggle the switch;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oinclude & oinclude::footer () 

{
	if (this->mstate < 0) 
	{
		this->mstate = -this->mstate;
		std::cout << "#endif" << std::endl;
		std::cout << std::endl;
	}
	return (*this);
}


/*====================================================================*
 *
 *   oinclude(char const *title, char const *label);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oinclude::oinclude (char const *title, char const *label) 

{
	this->mtitle = oinclude::save (title);
	this->mclass = oinclude::save (label);
	this->mstate = 0;
	return;
}


/*====================================================================*
 *
 *   oinclude()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
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
 *   ~oinclude()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oinclude::~oinclude () 

{
	delete [] this->mtitle;
	delete [] this->mclass;
	return;
}


/*====================================================================*
 *   end definition
 *--------------------------------------------------------------------*/

#endif

