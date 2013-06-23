/*====================================================================*
 *
 *   call.c - print C language call dependencies;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/oputoptv.hpp"
#include "../classes/oascii.hpp"
#include "../classes/ocpluswords.hpp"
#include "../classes/okeywords.hpp"
#include "../classes/oflagword.hpp"
#include "../classes/ofileopen.hpp"
#include "../classes/opathspec.hpp"
#include "../classes/odiscard.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oerror.cpp"
#include "../classes/oascii.cpp"
#include "../classes/ocpluswords.cpp"
#include "../classes/okeywords.cpp"
#include "../classes/oflagword.cpp"
#include "../classes/owildcard.cpp"
#include "../classes/ofileopen.cpp"
#include "../classes/ofilespec.cpp"
#include "../classes/opathspec.cpp"
#include "../classes/ocontext.cpp"
#include "../classes/odiscard.cpp"
#include "../classes/otext.cpp"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define CALL_B_BAILOUT 	(1 << 0)
#define CALL_B_VERBOSE 	(1 << 1)
#define CALL_B_SILENCE 	(1 << 2)
#define CALL_B_INVERT 	(1 << 3)

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

oflagword flagword;
ocpluswords keywords;
odiscard discard;

/*====================================================================*
 *
 *   signed function (signed c, signed e);
 *
 *   scan source file for C language function definitions and calls;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static signed function (signed c, signed e) 

{
	static unsigned level = 0;
	char module [512];
	char string [512];
	while (oascii::nobreak (e)) 
	{
		if (oascii::isspace (c)) 
		{
			c = std::cin.get ();
			continue;
		}
		if (c == '#') 
		{
			do 
			{
				c = discard.command (c, '\n');
			}
			while (oascii::isspace (c));
			continue;
		}
		if ((c == '{') || (c == '(') || (c == '[')) 
		{
			c = std::cin.get ();
			level++;
			continue;
		}
		if ((c == '}') || (c == ')') || (c == ']')) 
		{
			c = std::cin.get ();
			level--;
			continue;
		}
		if (c == '/') 
		{
			c = discard.comment (c);
			continue;
		}
		if (oascii::isquote (c)) 
		{
			c = discard.literal (c);
			continue;
		}
		if (oascii::isalpha (c) || (c == '_')) 
		{
			char * sp = string;
			do 
			{
				* sp++ = (char)(c);
				c = std::cin.get ();
			}
			while (isalnum (c) || (c == '_'));
			* sp = (char)(0);

#if 1

			std::cerr << string << std::endl;

#endif

			if (keywords.defined (string)) 
			{
				continue;
			}
			while (oascii::isspace (c)) 
			{
				c = std::cin.get ();
			}
			if (c == '(') 
			{
				if (!level) 
				{
					std::strcpy (module, string);
				}
				else if (flagword.anyset (CALL_B_INVERT)) 
				{
					std::cout << string << ":" << module << ";" << std::endl;
				}
				else 
				{
					std::cout << module << ":" << string << ";" << std::endl;
				}
			}
			continue;
		}
		if (oascii::isdigit (c)) 
		{
			do 
			{
				c = std::cin.get ();
			}
			while (oascii::isdigit (c) || (c == '.'));
			if ((c == 'x') || (c == 'X')) 
			{
				do 
				{
					c = std::cin.get ();
				}
				while (oascii::isxdigit (c));
			}
			if ((c == 'e') || (c == 'E')) 
			{
				c = std::cin.get ();
				if ((c == '+') || (c == '-')) 
				{
					c = std::cin.get ();
				}
				while (oascii::isdigit (c)) 
				{
					c = std::cin.get ();
				}
			}
			continue;
		}
		c = std::cin.get ();
	}
	return (c);
}

/*====================================================================*
 *   
 *   int main (int argc, char const * argv[]);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"x",
		oPUTOPTV_S_FUNNEL,
		"print C language call dependencies",
		"x\tinvert relationships",
		(char const *) (0)
	};
	ogetoptv getopt;
	opathspec pathspec;
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'x':
			flagword.setbits (CALL_B_INVERT);
			break;
		default:
			break;
		}
	}
	if (!getopt.argc ()) 
	{
		function (std::cin.get (), EOF);
	}
	while (getopt.argc () && * getopt.argv ()) 
	{
		char filename [FILENAME_MAX];
		pathspec.fullpath (filename, * getopt.argv ());
		if (std::freopen (filename, "rb", stdin)) 
		{
			c = function (std::cin.get (), EOF);
		}
		getopt++;
	}
	std::exit (0);
}

