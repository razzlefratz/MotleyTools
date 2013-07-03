/*====================================================================*
 *
 *   ochrtable.hpp - declaration of ochrtable class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCHRTABLE_HEADER
#define oCHRTABLE_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/ochrtbl.hpp"

/*====================================================================*
 *   class declaration;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ochrtable: public ochrtbl 

{
public:
	ochrtable ();
	virtual~ ochrtable ();
	ochrtable & tolower ();
	ochrtable & toupper ();
	ochrtable & toindex ();
	ochrtable & charset (char const * charset1, char const * charset2);
protected:
	ochrtable & mreset ();
	unsigned char * mtable;
private:
	unsigned c;
};

/*====================================================================*
 *   end declaration;
 *--------------------------------------------------------------------*/

#endif

