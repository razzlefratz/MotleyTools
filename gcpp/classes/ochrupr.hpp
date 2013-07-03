/*====================================================================*
 *
 *   ochrupr.hpp - declaration of ochrupr class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCHRUPR_HEADER
#define oCHRUPR_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/ochrtbl.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ochrupr: public ochrtbl 

{
public:
	ochrupr ();
	virtual~ ochrupr ();
protected:
	private: static const unsigned char table [];
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

