/*====================================================================*
 *
 *   calend2.cpp - print html calendar page;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <ctime>
#include <cstdlib>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/ocalendar.hpp"
#include "../classes/odate.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oindent.cpp"
#include "../classes/oindex.cpp"
#include "../classes/ocalendar.cpp"
#include "../classes/omonth.cpp"
#include "../classes/odate.cpp"
#include "../classes/otext.cpp"
#endif

/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main(int argc, char const * argv[])

{
	static char const * optv[] = 
	{
		"m:y:",
		oPUTOPTV_S_FILTER,
		"print html calendar on stdout",
		"m n\tmonth is (n)",
		"y n\tyear is (n)",
		(char const *)(0)
	};
	ogetoptv getopt;
	ocalendar * calendar;
	time_t now = time((time_t *)(0));
	struct tm * tm = localtime(& now);
	unsigned year = 1900 +  tm->tm_year;
	signed month = tm->tm_mon;
	signed c;
	while (~ (c = getopt.getoptv(argc, argv, optv)))
	{
		switch (c)
		{
		case 'y':
			year = std::atoi(getopt.optarg());
			break;
		case 'm':
			month = std::atoi(getopt.optarg());
			month--;
			break;
		default: 
			break;
		}
	}
	calendar = new ocalendar(year);
	calendar->annum();
	std::exit(0);
}

