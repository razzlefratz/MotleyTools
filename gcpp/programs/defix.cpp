/*====================================================================*
 *
 *   defix.cpp -
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstddef>
#include <cstdio>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/ocontext.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/ocontext.cpp"
#include "../classes/otext.cpp"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define FORMAT "%s\n"
#define CBREAK '.'

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv [])

{
	static char const * optv [] =
	{
		"c:f:iomps",
		oPUTOPTV_S_DIVINE,
		"extract and format prefix or suffix from string arguments",
		"c c\tcomponent separator is (c) [" LITERAL (CBREAK) "]",
		"f s\tformat string is (s) [" LITERAL (FORMAT) "]",
		"i\tbreak on initial separator",
		"m\tseparator is mandatory",
		"o\tseparator is optional",
		"p\textract prefix",
		"s\textract suffix",
		(char const *) (0)
	};
	ogetoptv getopt;
	ocontext string;
	char const * format = FORMAT;
	char character = CBREAK;
	bool initial = false;
	bool optional = false;
	bool prefix = false;
	signed c;
	while (~ (c = getopt.getoptv (argc, argv, optv)))
	{
		switch ((char) (c))
		{
		case 'c':
			character = * getopt.optarg ();
			break;
		case 'f':
			format = getopt.optarg ();
			break;
		case 'i':
			initial = true;
			break;
		case 'm':
			optional = false;
			break;
		case 'o':
			optional = true;
			break;
		case 'p':
			prefix = true;
			break;
		case 's':
			prefix = false;
			break;
		default: 
			break;
		}
	}
	while (getopt.argc () && * getopt.argv ())
	{
		string.split (* getopt.argv (), character, initial, optional);
		std::printf (format, (prefix)? string.prefix (): string.suffix ());
		getopt++;
	}
	return (0);
}

