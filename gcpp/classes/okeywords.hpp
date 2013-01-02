/*====================================================================*
 *
 *   okeywords.hpp - okeywords class definitions and declaration;
 *
 *   implement a generic keyword lookup table;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oKEYWORDS_HEADER
#define oKEYWORDS_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstddef>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"

/*====================================================================*
 *   interface declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) okeywords 

{
public:
	okeywords ();
	virtual ~ okeywords ();
	size_t count () const;
	char const * keywords (size_t index) const;
	bool defined (char const *string) const;
	size_t longest () const;
	size_t indexof (char const * string) const;
	okeywords & enumerate ();
	okeywords & enumerate (char const * prefix, char const * suffix);
	okeywords & enumerate (size_t columns);
protected:
	okeywords & mcheck ();
	char const * mtitle;
	char const ** mtable;
	size_t mcount;
private:
	static const unsigned words;
	static char const * table [];
};


/*====================================================================*
 *   end defintions;
 *--------------------------------------------------------------------*/

#endif

