/*====================================================================*
 *
 *   ocalendar.cpp - implementation of the ocalendar class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCALENDAR_SOURCE
#define oCALENDAR_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/date.h"
#include "../classes/ocalendar.hpp"
#include "../classes/oversion.hpp"

/*====================================================================*
 *   class constants; 
 *--------------------------------------------------------------------*/

#define HEADERSIZE 3 * DAYS_IN_WEEK 

/*====================================================================*
 *   class variables;
 *--------------------------------------------------------------------*/

char const * ocalendar::mdays [DAYS_IN_WEEK] = 

{
	" S",
	" M",
	" T",
	" W",
	" T",
	" F",
	" S"
};

char const * ocalendar::mdate1 [DATES_IN_MONTH+1] = 

{
	"&nbsp",
	" 1",
	" 2",
	" 3",
	" 4",
	" 5",
	" 6",
	" 7",
	" 8",
	" 9",
	"10",
	"11",
	"12",
	"13",
	"14",
	"15",
	"16",
	"17",
	"18",
	"19",
	"20",
	"21",
	"22",
	"23",
	"24",
	"25",
	"26",
	"27",
	"28",
	"29",
	"30",
	"31"
};

char const * ocalendar::mdate2 [DATES_IN_MONTH+1] = 

{
	"&nbsp;",
	" 1",
	" 2",
	" 3",
	" 4",
	" 5",
	" 6",
	" 7",
	" 8",
	" 9",
	"10",
	"11",
	"12",
	"13",
	"14",
	"15",
	"16",
	"17",
	"18",
	"19",
	"20",
	"21",
	"22",
	"23",
	"24",
	"25",
	"26",
	"27",
	"28",
	"29",
	"30",
	"31"
};

/*====================================================================*
 *
 *   ocalendar & stylesheet (unsigned level, unsigned space)
 *
 *   print CSS stylesheet having tags matching those of the calendar
 *   HTML elements;
 *
 *--------------------------------------------------------------------*/

ocalendar & ocalendar::stylesheet (unsigned level, unsigned space) 

{
	mindent.print (level++, space, "<style type='text/css'>");
	mindent.print (level, space, "table.annum { background:transparent; border:none; table-layout:fixed; cell-spacing:2px; border-collapse:separate; border-spacing:2px; width: 100%; }");
	mindent.print (level, space, "td.annum { padding:0px; }");
	mindent.print (level, space, "table.month { background:inherit; table-layout:fixed; border-collapse:separate; border:solid 1pt #000000; border-spacing:2px; }");
	mindent.print (level, space, "th.month { background: inherit; border: solid 1px #000000; padding: 2px 2px; font: normal 9pt comic sans ms; text-align:center;  }");
	mindent.print (level, space, "th.week  { background: inherit; border: solid 1px #000000; padding: 2px 2px; font: normal 9pt comic sans ms; text-align:center; }");
	mindent.print (level, space, "td.date  { background: inherit; border: solid 1px #C0C0C0; height: 25px; padding: 2px 2px; font: normal 9pt comic sans ms; vertical-align: top; text-align: right; width: 100px; }");
	mindent.print (level, space, "td.note  { background: #C0C0C0; border: solid 1px #C0C0C0; height: 25px; padding: 2px 2px; font: normal 9pt comic sans ms; vertical-align: top; text-align: right; }");
	mindent.print (level, space, "td.due   { background: #FFFF00; border: solid 1px #C0C0C0; height: 25px; padding: 2px 2px; font: normal 9pt comic sans ms; vertical-align: middle; text-align: center; }");
	mindent.print (level--, space, "</style>");
	return (* this);
}

/*====================================================================*
 *
 *   ocalendar & annum ()
 *
 *   print callendar year in HTML format as a complete page;
 *
 *--------------------------------------------------------------------*/

ocalendar & ocalendar::annum () 

{
	unsigned level = 0;
	unsigned space = 1;
	mindent.print (level, space, "<?xml version='1.0' encoding='iso-8859-1'?>");
	mindent.print (level, space, "<!DOCTYPE HTML PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN'>");
	mindent.print (level++, space, "<html xmlns='http://www.w3.org/1999/xhtml' lang='en-us'>");
	mindent.print (level++, space, "<head>");
	mindent.print (level++, space, "<title>");
	mindent.print (level--, space, "</title>");
	mindent.print (level, space, "<link href='calendar.css' rel='stylesheet' type='text/css'>");
	mindent.print (level--, space, "</head>");
	mindent.print (level++, space, "<body>");
	this->stylesheet (level, space).annum (level, space);
	mindent.print (level--, space, "</body>");
	mindent.print (level--, space, "</html>");
	return (* this);
}

/*====================================================================*
 *
 *   ocalendar & annum (unsigned level, unsigned space);
 *
 *   print calendar year in HTML format as one table of 3 columns
 *   and 4 rows with one month in each table cell formatted as an
 *   independent table;
 *
 *--------------------------------------------------------------------*/

ocalendar & ocalendar::annum (unsigned level, unsigned space) 

{
	mindent.print (level++, 1, "<table class='annum'>");
	for (unsigned row = 0; row < QUARTERS_IN_YEAR; row++) 
	{
		mindent.print (level++, 1, "<tr>");
		for (unsigned col = 0; col < MONTHS_IN_QUARTER; col++) 
		{
			mindent.print (level++, 1, "<td class='annum'>");
			ocalendar::month (level, space, row * MONTHS_IN_QUARTER + col);
			mindent.print (level--, 1, "</td>");
		}
		mindent.print (level--, 1, "</tr>");
	}
	mindent.print (level--, 1, "</table>");
	return (* this);
}

/*====================================================================*
 *
 *   ocalendar & month (unsigned index)
 *
 *   print given month in HTML format as one table within one page;
 *
 *--------------------------------------------------------------------*/

ocalendar & ocalendar::month (unsigned index) 

{
	unsigned level = 0;
	unsigned space = 1;
	mindent.print (level, space, "<?xml version='1.0' encoding='iso-8859-1'?>");
	mindent.print (level, space, "<!DOCTYPE HTML PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN'>");
	mindent.print (level++, space, "<html xmlns='http://www.w3.org/1999/xhtml' lang='en-us'>");
	mindent.print (level++, space, "<head>");
	mindent.print (level++, space, "<title>");
	mindent.print (level--, space, "</title>");
	mindent.print (level, space, "<link href='calendar.css' rel='stylesheet' type='text/css'>");
	mindent.print (level--, space, "</head>");
	mindent.print (level++, space, "<body>");
	this->stylesheet (level, space).month (level, space, index);
	mindent.print (level--, space, "</body>");
	mindent.print (level--, space, "</html>");
	return (* this);
}

/*====================================================================*
 *
 *   ocalendar & month (unsigned level, unsigned space, unsigned index);
 *
 *   print given month in HTML format as one table;
 *
 *--------------------------------------------------------------------*/

ocalendar & ocalendar::month (unsigned level, unsigned space, unsigned index) 

{
	omonth * month = this->mmonth [index];
	month->encode (this->mtitle, HEADERSIZE);
	mindent.print (level++, space, "<table class='month'>");
	mindent.print (level++, space, "<tr>");
	mindent.print (level++, space, "<th class='month' colspan='7'>");
	mindent.print (level, space, this->mtitle);
	mindent.print (level--, space, "</th>");
	mindent.print (level--, space, "</tr>");
	mindent.print (level++, space, "<tr>");
	for (unsigned weekday = 0; weekday < DAYS_IN_WEEK; weekday++) 
	{
		mindent.print (level++, space, "<th class='week'>");
		mindent.print (level, space, ocalendar::mdays [weekday]);
		mindent.print (level--, space, "</th>");
	}
	mindent.print (level--, space, "</tr>");
	for (unsigned week = 0; week < WEEKS_IN_MONTH; week++) 
	{
		mindent.print (level++, space, "<tr>");
		for (unsigned weekday = 0; weekday < DAYS_IN_WEEK; weekday++) 
		{
			unsigned date = month->date (week, weekday);
			mindent.print (level++, space, "<td class='date'>");
			mindent.print (level, space, ocalendar::mdate2 [date]);
			mindent.print (level--, space, "</td>");
		}
		mindent.print (level--, space, "</tr>");
	}
	mindent.print (level--, space, "</table>");
	return (* this);
}

/*====================================================================*
 *
 *   ocalendar & print ()
 *
 *
 *--------------------------------------------------------------------*/

ocalendar & ocalendar::print (unsigned index) 

{
	omonth * month = this->mmonth [index];
	month->encode (this->mtitle, HEADERSIZE);
	std::cout << " " << this->mtitle << std::endl;
	std::cout << "  S  M  T  W  T  F  S" << std::endl;
	for (unsigned week = 0; week < WEEKS_IN_MONTH; week++) 
	{
		for (unsigned weekday = 0; weekday < DAYS_IN_WEEK; weekday++) 
		{
			unsigned date = month->date (week, weekday);
			std::cout << " " << ocalendar::mdate1 [date];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return (* this);
}

/*====================================================================*
 *
 *   ocalendar ()
 *
 *   generate calendar covering jan thru dec of current year; 
 *
 *
 *--------------------------------------------------------------------*/

ocalendar::ocalendar () 

{
	this->mtitle = new char [HEADERSIZE];
	this->mmonth = new omonth * [MONTHS_IN_YEAR];
	for (signed month = 0; month < MONTHS_IN_YEAR; month++) 
	{
		this->mmonth [month] = new omonth (month);
	}
	return;
}

/*====================================================================*
 *
 *   ocalendar (unsigned year)
 *
 *   generate calendar covering jan thru dec of given year; 
 *
 *
 *--------------------------------------------------------------------*/

ocalendar::ocalendar (unsigned year) 

{
	this->mtitle = new char [HEADERSIZE];
	this->mmonth = new omonth * [MONTHS_IN_YEAR];
	for (signed month = 0; month < MONTHS_IN_YEAR; month++) 
	{
		this->mmonth [month] = new omonth (year, month);
	}
	return;
}

/*====================================================================*
 *
 *   ~ocalendar ()
 *
 *
 *
 *--------------------------------------------------------------------*/

ocalendar::~ocalendar () 

{
	delete [] this->mmonth;
	delete [] this->mtitle;
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

