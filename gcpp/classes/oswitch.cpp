/*====================================================================*
 *
 *   oswitch.cpp - definition of oswitch class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oSWITCH_SOURCE
#define oSWITCH_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <cstring>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oswitch.hpp"

/*====================================================================*
 *   class variables;     
 *--------------------------------------------------------------------*/

char const * oswitch::mstate [] = 

{
	"0",
	"1",
	"false",
	"true",
	"no",
	"yes",
	"off",
	"on",
	"disable",
	"enable",
	"down",
	"up",
	"stop",
	"start",
	"deny",
	"allow",
	(char const *)(0)
};


/*====================================================================*
 *
 *   bool state (char const *string, bool state);
 *
 *   lookup a state name and return the boolean value for that state;
 *   return the default state if the state name is undefined; lookup
 *   is case insensitive;
 *
 *   state table names are stored in pairs such that false states are
 *   stored at even offsets and true states at odd offsets; the state
 *   is then the offset modulo 2; the table can be expanded by adding
 *   name pairs at the correct offsets prior to the table end;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oswitch::state (char const *string, bool state) 

{
	for (unsigned index = 0; this->mstate [index]; index++) 
	{
		if (!strcasecmp (this->mstate [index], string)) 
		{
			return (index & 1);
		}
	}
	return (state);
}


/*====================================================================*
 *
 *   oswitch() 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oswitch::oswitch () 

{
	return;
}


/*====================================================================*
 *
 *   ~oswitch() 
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oswitch::~oswitch () 

{
	return;
}


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

