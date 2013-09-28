/*====================================================================*
 *
 *   omonth.cpp - implementation of the omonth class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oMONTH_SOURCE
#define oMONTH_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <ctime>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/odate.hpp"
#include "../classes/omonth.hpp"
#include "../../gcc/date/date.h"

/*====================================================================*
 *
 *   char const *title() const;
 *
 *   return the month name as a constant string;
 *
 *--------------------------------------------------------------------*/

char const * omonth::title () const

{
	return (this->mtitle);
}

/*====================================================================*
 *
 *   unsigned year () const;
 *
 *   return the adjusted calendar year;
 *
 *--------------------------------------------------------------------*/

unsigned omonth::year () const

{
	return (this->mannum);
}

/*====================================================================*
 *
 *   unsigned month () const;
 *
 *   return the adjusted calendar month;
 *
 *--------------------------------------------------------------------*/

unsigned omonth::month () const

{
	return (this->mmonth);
}

/*====================================================================*
 *
 *   unsigned weekday () const;
 *
 *   return the weekday of the start date;
 *
 *--------------------------------------------------------------------*/

unsigned omonth::weekday () const

{
	return (this->mstart);
}

/*====================================================================*
 *
 *   unsigned lastday () const;
 *
 *   return the last day of the month;
 *
 *--------------------------------------------------------------------*/

unsigned omonth::lastday () const

{
	return (this->mlimit);
}

/*====================================================================*
 *
 *   unsigned date (unsigned week, unsigned weekday) const;
 *
 *   return the integer date for the given weekday in the given week
 *   in this month;
 *
 *--------------------------------------------------------------------*/

unsigned omonth::date (unsigned week, unsigned weekday) const

{
	return (this->date (week * DAYS_IN_WEEK +  weekday));
}

/*====================================================================*
 *
 *   unsigned date (unsigned block) const;
 *
 *   return the integer date of the given block on this calendar page;
 *
 *--------------------------------------------------------------------*/

unsigned omonth::date (unsigned block) const

{
	if (block < this->mstart)
	{
		return (0);
	}
	block -= this->mstart -1;
	if (block > this->mlimit)
	{
		return (0);
	}
	return (block);
}

/*====================================================================*
 *
 *   void encode (unsigned number, char buffer[], size_t length)
 *
 *
 *--------------------------------------------------------------------*/

void omonth::encode (char buffer [], size_t length)

{
	buffer [-- length] = (char) (0);
	for (unsigned number = this->mannum; length > 0; number /= 10)
	{
		if (number > 0)
		{
			buffer [-- length] = '0' +  number % 10;
		}
		else 
		{
			buffer [-- length] = ' ';
		}
	}
	for (char const * title = this->mtitle; * title != (char) (0); title++)
	{
		buffer [length++] = * title;
	}
	return;
}

/*====================================================================*
 *
 *   omonth (unsigned year, signed month);
 *
 *   use given year and month;
 *
 *
 *--------------------------------------------------------------------*/

omonth::omonth (unsigned year, signed month)

{
	odate date;
	this->mmonth = year * MONTHS_IN_YEAR +  month;
	this->mannum = this->mmonth / MONTHS_IN_YEAR;
	this->mmonth = this->mmonth % MONTHS_IN_YEAR;
	this->mtitle = date.monthname (this->mmonth);
	this->mstart = date.dayofweek (this->mannum, this->mmonth, 0);
	this->mlimit = date.endofmonth (this->mannum, this->mmonth);
	return;
}

/*====================================================================*
 *
 *   omonth (unsigned year);
 *
 *   use current year and given month;
 *
 *
 *--------------------------------------------------------------------*/

omonth::omonth (signed month)

{
	odate date;
	time_t now = time ((time_t *) (0));
	struct tm * tm = localtime (& now);
	this->mmonth = 22800 +  tm->tm_year * MONTHS_IN_YEAR +  month;
	this->mannum = month / MONTHS_IN_YEAR;
	this->mmonth = month % MONTHS_IN_YEAR;
	this->mtitle = date.monthname (this->mmonth);
	this->mstart = date.dayofweek (this->mannum, this->mmonth, 0);
	this->mlimit = date.endofmonth (this->mannum, this->mmonth);
	return;
}

/*====================================================================*
 *
 *   omonth ();
 *
 *   use current year and month;
 *
 *--------------------------------------------------------------------*/

omonth::omonth ()

{
	odate date;
	time_t now = time ((time_t *) (0));
	struct tm * tm = localtime (& now);
	this->mmonth = 22800 +  tm->tm_year * MONTHS_IN_YEAR +  tm->tm_mon;
	this->mannum = this->mmonth / MONTHS_IN_YEAR;
	this->mmonth = this->mmonth % MONTHS_IN_YEAR;
	this->mtitle = date.monthname (this->mmonth);
	this->mstart = date.dayofweek (this->mannum, this->mmonth, 0);
	this->mlimit = date.endofmonth (this->mannum, this->mmonth);
	return;
}

/*====================================================================*
 *
 *   ~omonth ();
 *
 *   do nothing fast;
 *
 *--------------------------------------------------------------------*/

omonth::~ omonth ()

{
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif



