/*====================================================================*
 *
 *   oprogram.hpp - oprogram class declaration;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPROGRAM_HEADER
#define oPROGRAM_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/osource.hpp"
#include "../classes/oindent.hpp"

/*====================================================================*
 *   interface declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) oprogram: public osource, public oindent 

{
public:
	oprogram ();
	virtual ~ oprogram ();
	signed css2 (signed c);
	signed java (signed c);
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif 

