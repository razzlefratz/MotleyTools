/*====================================================================*
 *
 *   set.h-
 *
 *   Macros that look like sigaddset et al. but aren't; They are 
 *   used to manipulate bits in an integer, to do our signal bookeeping.
 *
 *--------------------------------------------------------------------*/

#ifndef SET_SOURCE
#define SET_SOURCE

#define ISMEMBER(set, bit) ((set) & (1 << (bit)))
#define DELSET(set, bit)   ((set) &= ~(1 << (bit)))
#define ADDSET(set, bit)   ((set) |= (1 << (bit)))
#define EMPTYSET(set)      ((set) = 0)

#endif

