/*====================================================================*
 *
 *   token.h - generic data type definitions and declarations; 
 *
 *.  Motley Tools by Charles Maier
 *:  modified tue 16 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TOKEN_HEADER
#define TOKEN_HEADER

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

typedef struct classvalue 

{ 
	unsigned class; 
	unsigned value; 
	char const * title; 
} 

classvalue; 

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

signed ClassValueTest (struct classvalue table [], unsigned limit); 
char const * ClassValueFind (struct classvalue table [], unsigned limit, unsigned class, unsigned value, char const * title); 

/*====================================================================*
 *   end definitions and declarations;
 *--------------------------------------------------------------------*/

#endif



