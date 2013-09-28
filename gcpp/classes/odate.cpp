/*====================================================================*
 *
 *   odate.cpp - implementation of the odate class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oDATE_SOURCE
#define oDATE_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/odate.hpp"
#include "../../gcc/date/date.h"

/*====================================================================*
 *   class opbjects;
 *--------------------------------------------------------------------*/

oindex odate::mindex;

/*====================================================================*
 *   class variables;
 *--------------------------------------------------------------------*/

char const * odate::months [MONTHS_IN_YEAR +  1] =

{
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December",
	(char const *) (0)
};

char const * odate::weekdays [DAYS_IN_WEEK +  1] =

{
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
	(char const *) (0)
};

/*====================================================================*
 *
 *   char const * monthname (unsigned month);
 *
 *   return the name of the month;
 *
 *--------------------------------------------------------------------*/

char const * odate::monthname (signed month)

{
	month = odate::mindex.qmod (month, MONTHS_IN_YEAR);
	return (odate::months [month]);
}

/*====================================================================*
 *
 *   char const * weekdayname (unsigned weekday);
 *
 *   return the name of the weekday;
 *
 *--------------------------------------------------------------------*/

char const * odate::weekdayname (signed weekday)

{
	weekday = odate::mindex.qmod (weekday, DAYS_IN_WEEK);
	return (odate::weekdays [weekday]);
}

/*====================================================================*
 *
 *   bool isleap(unsigned year);
 *
 *   return true of the given year is a leap year; leap years repeat
 *   every four years except at the turn of the century except every
 *   fourth century;
 *
 *
 *--------------------------------------------------------------------*/

bool odate::isleap (unsigned year)

{
	return (((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))));
}

/*====================================================================*
 *
 *   unsigned dayofweek(unsigned year, signed month, signed date);
 *
 *   return the weekday for a given date as integer 0 thru 6; the
 *   month and date are specified as zero based integers; this is
 *   done to support values in struct tm as defined in time.h;
 *
 *   the function value can be the index into the string vector
 *   sv_wkday[] to retrieve the weekday name string;
 *
 *      0=sunday, 1=monday, ... 6=saturday;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

unsigned odate::dayofweek (unsigned year, signed month, signed day)

{
	unsigned century;
	odate::normalize (& year, & month);
	if (month > 1)
	{
		-- month;
	}
	else 
	{
		month += MONTHS_IN_YEAR;
		-- month;
		-- year;
	}
	century = year / 100;
	year = year % 100;
	day += (26 * month -1) / 10 +  5 * year / 4 +  century / 4 - 2 * century +  1;
	return (odate::mindex.qmod (day, DAYS_IN_WEEK));
}

/*====================================================================*
 *
 *   unsigned dayofyear (unsigned year, signed month, signed day);
 *
 *
 *
 *--------------------------------------------------------------------*/

unsigned odate::dayofyear (unsigned year, signed month, signed day)

{
	static const signed days [MONTHS_IN_YEAR] =
	{
		0,
		31,
		59,
		90,
		120,
		151,
		181,
		212,
		243,
		273,
		304,
		334
	};
	month += year * MONTHS_IN_YEAR;
	year = month / MONTHS_IN_YEAR;
	month = month % MONTHS_IN_YEAR;
	day += days [month];
	if ((day > days [1]) && odate::isleap (year))
	{
		day++;
	}
	return (day);
}

/*====================================================================*
 *
 *   unsigned endofmonth (unsigned year, signed month);
 *
 *   return the number of days in the given month in the given year;
 *
 *   month is a signed integer allowing relative references to prior
 *   months, possibley occuring in a prior year; for example, if year
 *   is 2001 then month -13 is december 1999;
 *
 *
 *--------------------------------------------------------------------*/

unsigned odate::endofmonth (unsigned year, signed month)

{
	static const unsigned days [MONTHS_IN_YEAR] =
	{
		31,
		28,
		31,
		30,
		31,
		30,
		31,
		31,
		30,
		31,
		30,
		31
	};
	unsigned day;
	odate::normalize (& year, & month);
	day = days [month];
	if ((month == 1) && odate::isleap (year))
	{
		day++;
	}
	return (day);
}

/*====================================================================*
 *
 *   void normalize(unsigned *year, signed *month)
 *
 *
 *
 *--------------------------------------------------------------------*/

void odate::normalize (unsigned * year, signed * month)

{
	* month += * year * MONTHS_IN_YEAR;
	* year = * month / MONTHS_IN_YEAR;
	* month %= MONTHS_IN_YEAR;
	return;
}

/*====================================================================*
 *
 *   odate ();
 *
 *
 *
 *--------------------------------------------------------------------*/

odate::odate ()

{
	return;
}

/*====================================================================*
 *
 *   ~odate ();
 *
 *
 *
 *--------------------------------------------------------------------*/

odate::~ odate ()

{
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif



