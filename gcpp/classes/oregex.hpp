/*====================================================================*
 *
 *   oregex.hpp - interface for the oregex class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oREGEX_HEADER
#define oREGEX_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oescape.hpp"
#include "../classes/oascii.hpp"

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define REGEX_POSIX_EXTENSIONS
#define REGEX_LABEL_EXTENSIONS
#define REGEX_COUNT_MAX 0x7FFF

#define REGEX_C_KLEENE_STAR ('*')
#define REGEX_C_KLEENE_ONCE ('?')
#define REGEX_C_KLEENE_PLUS ('+')

#define REGEX_C_SRT ('[')
#define REGEX_C_END (']')
#define REGEX_C_RNG ('-')
#define REGEX_C_NOT ('!')
#define REGEX_C_ESC ('\\')
#define REGEX_C_ANY ('.')
#define REGEX_C_BOL ('^')
#define REGEX_C_EOL ('$')
#define REGEX_S_SPAN (".*")

/*====================================================================*
 *7
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oregex 

{
public:
	oregex (char const * expression);
	virtual~ oregex ();
	size_t length (char const * string) const;
	char const * select (char const * string) const;
	char const * span (char const * string) const;
	oregex & show ();
private:
	static char const * charset (char const * string, char const c, char buffer [], size_t length);
	static bool compare (char const * charset, char const c, bool exclude);
	static char * fill (unsigned clower, unsigned cupper, char buffer [], size_t * length);
	oregex * mpattern;
	char * mcharset;
	bool mexclude;
	size_t mminimum;
	size_t mmaximum;
};


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

