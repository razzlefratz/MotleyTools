/*====================================================================*
 *
 *   ocalendar.hpp - interface for the ocalendar class;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCALENDAR_HEADER
#define oCALENDAR_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/oindent.hpp"
#include "../classes/omonth.hpp"

/*====================================================================*
 *   interface definition;
 *--------------------------------------------------------------------*/

class __declspec (dllexport) ocalendar 

{
public:
	ocalendar ();
	ocalendar (unsigned year);
	virtual ~ ocalendar ();
	ocalendar & annum ();
	ocalendar & month (unsigned index);
	ocalendar & annum (unsigned level, unsigned space);
	ocalendar & month (unsigned level, unsigned space, unsigned index);
	ocalendar & stylesheet (unsigned level, unsigned space);
	ocalendar & print (unsigned index);
private:
	omonth ** mmonth;
	oindent mindent;
	static char const * mdays [];
	static char const * mdate1 [];
	static char const * mdate2 [];
	char * mtitle;
};


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

