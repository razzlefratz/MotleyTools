/*====================================================================*
 *
 *   ochrlwr.hpp - declaration of ochrlwr class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCHRLWR_HEADER
#define oCHRLWR_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/ochrtbl.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ochrlwr: public ochrtbl

{
public: 
	ochrlwr ();
	virtual ~ ochrlwr ();
protected: 
private: 
	static const unsigned char table [];
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif



