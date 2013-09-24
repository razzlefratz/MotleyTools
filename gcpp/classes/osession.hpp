/*====================================================================*
 *
 *   osession.hpp - interface for the osession class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oENVIRON_HEADER
#define oENVIRON_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <ctime>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 * 
 *--------------------------------------------------------------------*/

class __declspec (dllexport) osession

{
public: 
	osession ();
	virtual ~ osession ();
	char const * hostname () const;
	char const * username () const;
	char const * datetime () const;
	size_t strfwhat (char buffer [], size_t length, char const * event);
	size_t strfdate (char buffer [], size_t length, time_t event);
	size_t strfwhen (char buffer [], size_t length, time_t event);
	size_t strfwhom (char buffer [], size_t length);
private: 
	char * mhostname;
	char * musername;
	char * mdatetime;
};

/*====================================================================*
 *   end class declaration;
 *--------------------------------------------------------------------*/

#endif



