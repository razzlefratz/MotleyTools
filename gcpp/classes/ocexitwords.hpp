/*====================================================================*
 *
 *   ocexitwords.hpp - declaration of ocexitword class;
 *
 *   this class implements the symbol table containg C language macro 
 *   processor strings;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCEXITWORDS_HEADER
#define oCEXITWORDS_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/okeywords.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ocexitwords: public okeywords 

{
public:
	ocexitwords ();
	~ ocexitwords ();
};


/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

