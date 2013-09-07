/*====================================================================*
 *
 *   classvalue.c
 *
 *   types.h - 
 *
 *
 *--------------------------------------------------------------------*/

#ifndef CLASSVALUE_SOURCE
#define CLASSVALUE_SOURCE

#include <stdio.h>
#include <stdint.h>

#include "../tools/token.h"
#include "../tools/types.h"

/*====================================================================*
 *
 *   void ClassValueTest (struct classvalue table [], unsigned size);
 *
 *   token.h
 *
 *
 *--------------------------------------------------------------------*/

signed ClassValueTest (struct classvalue table [], unsigned limit) 

{ 
	unsigned index; 
	for (index = 1; index < limit; ++ index) 
	{ 
		if (table [index].class > table [index - 1].class) 
		{ 
			continue; 
		} 
		if (table [index].class < table [index - 1].class) 
		{ 
			error (1, 0, "list [%d] type %d code %d is out of order.", index, table [index].class, table [index].value); 
		} 
		if (table [index].value > table [index - 1].value) 
		{ 
			continue; 
		} 
		if (table [index].value < table [index - 1].value) 
		{ 
			error (1, 0, "list [%d] type %d code %d is out of order.", index, table [index].class, table [index].value); 
		} 
		error (1, 0, "list [%d] type %d code %d is a duplicate.", index, table [index].class, table [index].value); 
	} 
	return; 
} 

/*====================================================================*
 *
 *   char const * ClassValueFind (struct classvalue table [], unsigned size, unsigned class, unsigned value);
 *
 *   token.h
 *
 *
 *--------------------------------------------------------------------*/

char const * ClassValueFind (struct classvalue table [], unsigned limit, unsigned class, unsigned value, char const * title) 

{ 
	size_t lower = 0; 
	size_t upper = limit; 
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
	return (title); 
} 

/*====================================================================*
 *   demo/test program;
 *--------------------------------------------------------------------*/

#if 0

static struct classvalue table [] = 

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
	}, 
	{ 
		0x0002, 
		0x02, 
		"Case 3"
	}, 
	{ 
		0x0005, 
		0x02, 
		"Case 4"
	}, 
	{ 
		0x0004, 
		0x02, 
		"Case 5"
	} 
}; 

int main (int argc, char const * argv []) 

{ 
	extern struct classvalue table []; 
	ClassValueTest (table, SIZEOF (table)); 
	return (0); 
} 

#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



