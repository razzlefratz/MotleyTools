/*====================================================================*
 *
 *   odate.hpp - interface for the odate class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oDATE_HEADER
#define oDATE_HEADER

/*====================================================================*
 *   custom header files; 
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oindex.hpp"

/*====================================================================*
 *   interface definition;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) odate 

{
public:
	odate ();
	virtual ~ odate ();
	static char const * months [];
	static char const * weekdays [];
	static char const * monthname (signed month);
	static char const * weekdayname (signed weekday);
	static bool isleap (unsigned year);
	static unsigned dayofweek (unsigned year, signed month, signed day);
	static unsigned dayofyear (unsigned year, signed month, signed day);
	static unsigned endofmonth (unsigned year, signed month);
	static void normalize (unsigned * year, signed * month);
protected:
private:
	static oindex mindex;
};


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

