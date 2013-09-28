/*====================================================================*
 *
 *   oputopt.cpp - implementation of the oputopt class.
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPUTOPT_SOURCE
#define oPUTOPT_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <iostream>
#include <cstdlib>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetopt.hpp"
#include "../classes/oputopt.hpp"

/*====================================================================*
 *
 *   oputopt & chkopt (char const * optv[], char const * options);
 *
 *--------------------------------------------------------------------*/

oputopt & oputopt::chkopt (char const * optv [], char const * options)

{
	extern char const * program_name;
	char const * option;
	signed index;
	for (option = options; * option; option++)
	{
		if (* option == ':')
		{
			continue;
		}
		for (index = oPUTOPT_I_DETAILS; optv [index]; index++)
		{
			if (* option == * optv [index])
			{
				break;
			}
		}
		if (optv [index])
		{
			continue;
		}
		std::cerr << program_name << ": option '" << * option << "' has no string" << std::endl;
	}
	for (index = oPUTOPT_I_DETAILS; optv [index]; index++)
	{
		for (option = options; * option; option++)
		{
			if (* option == ':')
			{
				continue;
			}
			if (* option == * optv [index])
			{
				break;
			}
		}
		if (* option)
		{
			continue;
		}
		std::cerr << program_name << ": string \"" << optv [index] << "\" has not option" << std::endl;
	}
	return (* this);
}

/*====================================================================*
 *
 *   oputopt & putopt(char const * usage[], signed exitcode);
 *
 *   print usage vector on stderr; this presents the user with a help
 *   summary; program_name is defined in ogetopt::getopt() but it could be
 *   defined in main or another component; getopt.h is included above
 *   for GETOPT_C_OPTIONS which is normally '-' but could be anything;
 *
 *--------------------------------------------------------------------*/

oputopt & oputopt::putopt (char const * usage [], signed exitcode)

{
	this->putopt (usage);
	std::exit (exitcode);
}

/*====================================================================*
 *
 *   oputopt & putopt(char const * usage[]);
 *
 *   print usage vector on stderr; this presents the user with a help
 *   summary; program_name is defined in ogetopt::getopt() but it could be
 *   defined in main or another component; getopt.h is included above
 *   for GETOPT_C_OPTIONS which is normally '-' but could be anything;
 *
 *--------------------------------------------------------------------*/

oputopt & oputopt::putopt (char const * usage [])

{
	extern char const * program_name;
	std::cout << std::endl;
	std::cout << " purpose: " << usage [oPUTOPT_I_PURPOSE] << std::endl << std::endl;
	std::cout << " command: " << program_name << " [options] " << usage [oPUTOPT_I_COMMAND] << std::endl << std::endl;
	std::cout << " options: [" << usage [oPUTOPT_I_OPTIONS] << oGETOPT_C_VERSION << oGETOPT_C_SUMMARY << "]" << std::endl << std::endl;
	for (int index = oPUTOPT_I_DETAILS; usage [index]; index++)
	{
		std::cout << " " << oGETOPT_C_OPTIONS << usage [index] << std::endl;
	}
	std::cout << " " << oGETOPT_C_OPTIONS << oGETOPT_C_VERSION << "\tversion information" << std::endl;
	std::cout << " " << oGETOPT_C_OPTIONS << oGETOPT_C_SUMMARY << "\thelp summary" << std::endl;
	std::cout << std::endl;
	return (* this);
}

/*====================================================================*
 *
 *   oputopt ();
 *
 *--------------------------------------------------------------------*/

oputopt::oputopt ()

{
	return;
}

/*====================================================================*
 *
 *   ~oputopt ();
 *
 *--------------------------------------------------------------------*/

oputopt::~ oputopt ()

{
	return;
}

/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif



