/*====================================================================*
 *
 *   double range(double sample[], size_t size, double *minimum, double *maximum, double *average, double *sigma);
 *
 *   calc.h
 *
 *   calculate the minimum, maximum, arithmetic mean and standard deviation 
 *   of a sample population; return the sample range as the function value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef RANGE_SOURCE
#define RANGE_SOURCE

#include <stdlib.h>
#include <math.h>

#include "../calc/calc.h"

double range (double list [], size_t size, double *minimum, double *maximum, double *average, double *sigma) 

{
	if (size) 
	{
		size_t item;
		double total = 0.0;
		double sumsq = 0.0;
		*minimum = *maximum = list [0];
		for (item = 0; item < size; item++) 
		{
			total += list [item];
			sumsq += list [item] * list [item];
			if (list [item] < *minimum) 
			{
				*minimum = list [item];
			}
			else if (list [item] > *maximum) 
			{
				*maximum = list [item];
			}
		}
		*average = total / size;
		*sigma = (double) (sqrt ((sumsq - ((total * total) / size)) / (size - 1)));
		return (*maximum - *minimum);
	}
	else 
	{
		*minimum = 0.0;
		*maximum = 0.0;
		*average = 0.0;
		*sigma = 0.0;
	}
	return (0);
}


#endif

