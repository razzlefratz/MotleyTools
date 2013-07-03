/*====================================================================*
 *
 *   osession.cpp - implementation of the osession class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oENVIRON_SOURCE
#define oENVIRON_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ctime>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/osession.hpp"
#include "../../gcc/date/date.h"
#include "../../gcc/tools/sizes.h"
#include "../../gcc/linux/getusername.c"

/*====================================================================*
 *
 *   char const * osession::hostname () const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * osession::hostname () const 

{
	return (this->mhostname);
}

/*====================================================================*
 *
 *   char const * osession::username () const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * osession::username () const 

{
	return (this->musername);
}

/*====================================================================*
 * 
 *   size_t osession::strfwhat (char buffer[], size_t length, char const * event);
 *
 *   return an event statement as a constant string; event statements are
 *   used for logging putposes;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

size_t osession::strfwhat (char buffer [], size_t length, char const * event) 

{
	time_t timer = std::time ((time_t *) (0));
	char * string = buffer;

#if defined (__linux__)

	string += std::snprintf (string, string - buffer + length, "%s", event);

#else

	string += snprintf (string, string - buffer + length, "%s", event);

#endif

	string += osession::strfwhen (string, string - buffer + length, timer);
	string += osession::strfwhom (string, string - buffer + length);
	return (string - buffer);
}

/*====================================================================*
 *
 *   size_t strfdate (char buffer[], size_t length, time_t event)
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

size_t osession::strfdate (char buffer [], size_t length, time_t event) 

{
	char * string = buffer;
	string += std::strftime (string, string - buffer + length, DAYTIME, std::localtime (& event));
	return (string - buffer);
}

/*====================================================================*
 * 
 *   char const * strfwhen (char buffer[], size_t length, time_t event);
 *
 *   return a when string as a constant string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

size_t osession::strfwhen (char buffer [], size_t length, time_t event) 

{
	char * string = buffer;

#if defined (__linux__)

	string += std::snprintf (string, string - buffer + length, " at ");
	string += std::strftime (string, string - buffer + length, "%T %Z", std::localtime (& event));
	string += std::snprintf (string, string - buffer + length, " on ");
	string += std::strftime (string, string - buffer + length, "%a %d %b %y", std::localtime (& event));

#else

	string += snprintf (string, string - buffer + length, " at ");
	string += strftime (string, string - buffer + length, "%T %Z", localtime (& event));
	string += snprintf (string, string - buffer + length, " on ");
	string += strftime (string, string - buffer + length, "%a %d %b %y", localtime (& event));

#endif

	return (string - buffer);
}

/*====================================================================*
 * 
 *   char const * strfwhom (char buffer[], size_t length);
 *
 *   return a show string as a constant string; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

size_t osession::strfwhom (char buffer [], size_t length) 

{
	char * string = buffer;

#if defined (__linux__)

	string += std::snprintf (string, string - buffer + length, " by");
	string += std::snprintf (string, string - buffer + length, " %s", this->musername);
	string += std::snprintf (string, string - buffer + length, " on");
	string += std::snprintf (string, string - buffer + length, " %s", this->mhostname);

#else

	string += snprintf (string, string - buffer + length, " by");
	string += snprintf (string, string - buffer + length, " %s", this->musername);
	string += snprintf (string, string - buffer + length, " on");
	string += snprintf (string, string - buffer + length, " %s", this->mhostname);

#endif

	return (string - buffer);
}

/*====================================================================*
 *
 *   osession();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osession::osession () 

{
	this->mhostname = new char [HOSTNAME_MAX];
	this->musername = new char [USERNAME_MAX];
	this->mdatetime = new char [DATETIME_MAX];
	if (gethostname (this->mhostname, HOSTNAME_MAX)) 
	{
		strcpy (this->mhostname, "localhost");
	}
	if (getusername (this->musername, USERNAME_MAX, getuid ())) 
	{
		strcpy (this->musername, "localuser");
	}
	return;
}

/*====================================================================*
 *
 *   ~osession();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

osession::~osession () 

{
	delete [] this->mhostname;
	delete [] this->musername;
	delete [] this->mdatetime;
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

