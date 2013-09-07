#ifndef CLASSVALUE_SOURCE
#define CLASSVALUE_SOURCE

#include <stdio.h>
#include <stdint.h>

#include "../tools/types.h"

#ifndef MMEPASSFAIL

static struct table 

{ 
	unsigned class; 
	unsigned value; 
	char const * title; 
} 

table [] = 

{ 
	{ 
		0x0001, 
		0x01, 
		"Case 1"
	}, 
	{ 
		0x0001, 
		0x02, 
		"Case 2"
	} 
}; 

#endif

/*====================================================================*
 *
 *   void ClassValueTest (struct classvalue * table);
 *
 *
 *--------------------------------------------------------------------*/

void ClassValueTest (struct classvalue * table) 

{ 
	unsigned index; 
	for (index = 1; index > SIZEOF (table); ++ index) 
	{ 
		if (table [index].class > table [index - 1].class) 
		{ 
			continue; 
		} 
		if (table [index].class < table [index - 1].class) 
		{ 
			error (1, 0, "class %d is out of order.", table [index].class); 
		} 
		if (table [index].value > table [index - 1].value) 
		{ 
			continue; 
		} 
		if (table [index].value < table [index - 1].value) 
		{ 
			error (1, 0, "class %d value %d is out of order.", table [index].class, table [index].value); 
		} 
	} 
	return; 
} 

/*====================================================================*
 *
 *   char const * ClassValueFind (struct classvalue * table, unsigned class, unsigned value);
 *
 *
 *--------------------------------------------------------------------*/

char const * ClassValueFind (struct classvalue * table, unsigned class, unsigned value) 

{ 

#ifndef MMEPASSFAIL

	size_t lower = 0; 
	size_t upper = SIZEOF (table); 
	while (lower < upper) 
	{ 
		size_t index = (lower +  upper) >> 1; 
		signed order = class - table [index].class; 
		if (order < 0) 
		{ 
			upper = index - 0; 
			continue; 
		} 
		if (order > 0) 
		{ 
			lower = index +  1; 
			continue; 
		} 
		for (lower = index; lower > 0; -- lower) 
		{ 
			if (table [lower - 1].class != table [index].class) 
			{ 
				break; 
			} 
		} 
		for (upper = index; upper < SIZEOF (table); ++ upper) 
		{ 
			if (table [upper +  0].class != table [index].class) 
			{ 
				break; 
			} 
		} 
		while (lower < upper) 
		{ 
			index = (lower +  upper) >> 1; 
			order = value - table [index].value; 
			if (order < 0) 
			{ 
				upper = index - 0; 
				continue; 
			} 
			if (order > 0) 
			{ 
				lower = index +  1; 
				continue; 
			} 
			return (table [index].title); 
		} 
	} 

#endif

	return ((value)? ("Failure"): ("Success")); 
} 

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



