/*====================================================================*
 *
 *   set.h - sigaddset-style macros for integers;
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SET_HEADER
#define SET_HEADER

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define ISMEMBER(map, bit) ((map) & (1 << (bit)))
#define DELSET(map, bit)   ((map) &= ~(1 << (bit)))
#define ADDSET(map, bit)   ((map) |= (1 << (bit)))
#define EMPTYSET(map)      ((map) = 0)

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

