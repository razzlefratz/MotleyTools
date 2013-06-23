/*====================================================================*
 *
 *   opage.hpp - interface for the opage class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPAGE_HEADER
#define oPAGE_HEADER

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#include <cstddef>

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/otext.hpp"

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define oPAGE_ROWS 60
#define oPAGE_COLS 78
#define oPAGE_TABS 8
#define LOGTIME_LEN 24
#define DAYTIME_LEN 28
#define LOGTIME "%F %T %Z"
#define DAYTIME "%T %a %d %b %Y %Z"

/*====================================================================*
 *   interface defintions;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) opage: private otext 

{
public:
	opage ();
	opage (char const * string);
	virtual~ opage ();
	char const * title () const;
	unsigned rows () const;
	unsigned cols () const;
	unsigned tabs () const;
	opage & title (char const * title);
	opage & rows (unsigned rows);
	opage & cols (unsigned cols);
	opage & tabs (unsigned tabs);
	signed put (signed c);
	opage & put (char const * string);
private:
	opage & header ();
	opage & footer ();
	char * mtitle;
	unsigned mrows;
	unsigned mcols;
	unsigned mtabs;
	unsigned mpage;
	unsigned mline;
	unsigned mrow;
	unsigned mcol;
};

/*====================================================================*
 *   end defintions;
 *--------------------------------------------------------------------*/

#endif

