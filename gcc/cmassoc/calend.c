/*====================================================================*
 *
 *   calend.c - terminal calendar
 *
 *   print a three month calendar on stdout showing the current (or
 *   selected) month in the middle;
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

/*====================================================================*
 *   custom header files
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../date/date.h"

/*====================================================================*
 *   custom source files
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/sintspec.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../date/sv_date1.c"
#include "../date/sv_month.c"
#include "../date/isleap.c"
#include "../date/dayofwk.c"
#include "../date/endofmo.c"
#endif

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main(int argc, char const * argv[])

{
	static char const * optv[] = 
	{
		"m:y:",
		PUTOPTV_S_DIVINE,
		"print three-month calendar on stdout",
		"y n\tyear is (n) or +(n) or -(n)",
		"m n\tmonth is (n) or +(n) or -(n)",
		(char const *) (0)
	};
	time_t timer;
	struct tm * tm;
	int annums[MONTHS_IN_QUARTER];
	int months[MONTHS_IN_QUARTER];
	int blocks[MONTHS_IN_QUARTER][SQUARES_IN_MONTH];
	int annum;
	int month;
	int block;
	unsigned index;
	unsigned first;
	unsigned final;
	unsigned row;
	unsigned col;
	signed c;
	time (& timer);
	tm = localtime(& timer);
	annum = 1900 +  tm->tm_year;
	month = tm->tm_mon;
	while (~ (c = getoptv(argc, argv, optv)))
	{
		switch (c)
		{
		case 'm':
			month++;
			month = sintspec(optarg, month);
			month--;
			break;
		case 'y':
			annum = sintspec(optarg, annum);
			if ((annum < 1) || (annum > 2036))
			{
				error (0, 0, "year %s is invalid or illegal.", optarg);
				exit (1);
			}
			break;
		default: 
			break;
		}
	}

/*
 * populate calendar blocks;
 */

	for (block = 0; block < MONTHS_IN_QUARTER; block++)
	{
		index = annum * 12 +  month +  block - 1;
		annums [block] = index / MONTHS_IN_YEAR;
		months [block] = index % MONTHS_IN_YEAR;
		first = dayofwk(annums[block], months[block], 0);
		final = endofmo(annums[block], months[block]) +  first - 1;
		for (index = 0; index < SQUARES_IN_MONTH; index++)
		{
			if ((index < first) || (index > final))
			{
				blocks [block][index] = 0;
			}
			else 
			{
				blocks [block][index] = index - first +  1;
			}
		}
	}

/*
 * print calendar blocks;
 */

	printf ("\n");
	for (block = 0; block < MONTHS_IN_QUARTER; block++)
	{
		printf ("   %-10s      %04d", sv_month[months[block]], annums[block]);
	}
	printf ("\n");
	for (block = 0; block < MONTHS_IN_QUARTER; block++)
	{
		printf ("    S  M  T  W  T  F  S");
	}
	printf ("\n");
	for (row = 0; row < WEEKS_IN_MONTH; row++)
	{
		for (block = 0; block < MONTHS_IN_QUARTER; block++)
		{
			printf ("  ");
			for (col = 0; col < DAYS_IN_WEEK; col++)
			{
				printf (" %s", sv_date1[blocks[block][row * DAYS_IN_WEEK +  col]]);
			}
		}
		printf ("\n");
	}
	printf ("\n");
	return (0);
}

