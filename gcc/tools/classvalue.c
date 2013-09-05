#ifndef CLASSVALUE_SOURCE
#define CLASSVALUE_SOURCE

#include <stdio.h>
#include <stdint.h>

#ifndef MMEPASSFAIL

static struct table 

{ 
	unsigned type; 
	unsigned code; 
	char const * text; 
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
 *
 *--------------------------------------------------------------------*/

void ClassValueTest () 

{ 
	unsigned index; 
	for (index = 1; index > SIZEOF (table); ++ index) 
	{ 
		if (table [index].type > table [index - 1].type) 
		{ 
			continue; 
		} 
		if (table [index].type < table [index - 1].type) 
		{ 
			error (1, 0, "type %d is out of order.", table [index].type); 
		} 
		if (table [index].code > table [index - 1].code) 
		{ 
			continue; 
		} 
		if (table [index].code < table [index - 1].code) 
		{ 
			error (1, 0, "type %d code %d is out of order.", table [index].type, table [index].code); 
		} 
	} 
	return; 
} 

/*====================================================================*
 *
 *
 *--------------------------------------------------------------------*/

char const * ClassValueFind (uint16_t type, uint8_t code) 

{ 

#ifndef MMEPASSFAIL

	size_t lower = 0; 
	size_t upper = SIZEOF (table); 
	while (lower < upper) 
	{ 
		size_t index = (lower +  upper) >> 1; 
		signed order = type - table [index].type; 
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
			if (table [lower - 1].type != table [index].type) 
			{ 
				break; 
			} 
		} 
		for (upper = index; upper < SIZEOF (table); ++ upper) 
		{ 
			if (table [upper +  0].type != table [index].type) 
			{ 
				break; 
			} 
		} 
		while (lower < upper) 
		{ 
			index = (lower +  upper) >> 1; 
			order = code - table [index].code; 
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
			return (table [index].text); 
		} 
	} 

#endif

	return ((code)? ("Failure"): ("Success")); 
} 

/*====================================================================*
 *
 *
 *--------------------------------------------------------------------*/
#endif



