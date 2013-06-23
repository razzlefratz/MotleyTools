/*====================================================================*
 *
 *   ofunctions.hpp - declaration of ofunctions class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oFUNCTIONS_HEADER
#define oFUNCTIONS_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/okeywords.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ofunctions: public okeywords 

{
public:
	ofunctions ();
	~ ofunctions ();
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

