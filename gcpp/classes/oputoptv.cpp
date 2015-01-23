/*====================================================================*
 *
 *   oputoptv.cpp - implementation of the oputoptv class.
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPUTOPTV_SOURCE
#define oPUTOPTV_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <iostream>
#include <cstdlib>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/oputoptv.hpp"

/*====================================================================*
 *
 *   oputoptv & chkoptv (char const * optv[]);
 *
 *--------------------------------------------------------------------*/

oputoptv & oputoptv::chkoptv (char const ** optv)

{
	extern char const * program_name;
	char const ** action;
	char const * option;
	optv++;
	optv++;
	for (option = * optv++; * option; option++)
	{
		if (* option == ':')
		{
			continue;
		}
		for (action = optv; * action; action++)
		{
			if (* option == ** action)
			{
				break;
			}
		}
		if (* action)
		{
			continue;
		}
		std::cerr << program_name << ": option '" << * option << "' has no action text" << std::endl;
	}
	for (action = optv--; * action; action++)
	{
		for (option = * optv; * option; option++)
		{
			if (* option == ':')
			{
				continue;
			}
			if (* option == ** action)
			{
				break;
			}
		}
		if (* option)
		{
			continue;
		}
		std::cerr << program_name << ": action text \"" << * action << "\" has no option" << std:endl;
	}
	return (* this);
}

/*====================================================================*
 *
 *   oputoptv & oputoptv (char const * optv[]);
 *
 *   print optv on stderr; this presents the user with a help summary;
 *
 *   program_name is defined in ogetopt::getoptv() but it could be
 *   defined in main or another component; ogetoptv.hpp is included
 *   above for GETOPTV_C_OPTIONS which is normally '-' but could be
 *   anything;
 *
 *--------------------------------------------------------------------*/

oputoptv & oputoptv::putoptv (char const ** optv)

{
	extern char const * program_name;
	std::cout << std::endl;
	std::cout << " program: " << * optv++ << std::endl << std::endl;
	std::cout << " command: " << program_name << " [options] " << * optv++ << std::endl << std::endl;
	std::cout << " options: [" << * optv++ << oGETOPTV_C_VERSION << oGETOPTV_C_SUMMARY << "]" << std::endl << std::endl;
	while (* optv)
	{
		std::cout << " " << oGETOPTV_C_OPTIONS << * optv++ << std::endl;
	}
	std::cout << " " << oGETOPTV_C_OPTIONS << oGETOPTV_C_VERSION << "\tversion information" << std::endl;
	std::cout << " " << oGETOPTV_C_OPTIONS << oGETOPTV_C_SUMMARY << "\thelp summary" << std::endl;
	std::cout << std::endl;
	return (* this);
}

/*====================================================================*
 *
 *   oputoptv & putoptv (char const * optv[], signed exitcode);
 *
 *   print optv vector on stderr; this presents the user with a help
 *   summary; program_name is defined in ogetoptv::getoptv() but it could be
 *   defined in main or another component; getoptv.h is included above
 *   for GETOPTV_C_OPTIONS which is normally '-' but could be anything;
 *
 *--------------------------------------------------------------------*/

oputoptv & oputoptv::putoptv (char const * optv [], signed exitcode)

{
	oputoptv::putoptv (optv);
	std::exit (exitcode);
}

/*====================================================================*
 *
 *   oputoptv ();
 *
 *--------------------------------------------------------------------*/

oputoptv::oputoptv ()

{
	return;
}

/*====================================================================*
 *
 *   ~oputoptv ();
 *
 *--------------------------------------------------------------------*/

oputoptv::~ oputoptv ()

{
	return;
}

/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif



