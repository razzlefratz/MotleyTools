/*====================================================================*
 *
 *   oclibwords.hpp - declaration of oclibwords class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCLIBWORDS_HEADER
#define oCLIBWORDS_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/okeywords.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec(dllexport) oclibwords: public okeywords

{
public: 
	oclibwords ();
	~ oclibwords();
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif



