/*====================================================================*
 *
 *   size_t chrindex (register char const *string, register unsigned c);
 *
 *   chrlib.h
 *
 *   return the position of a given character within a string; 
 *   return the  the string length if the search fails;
 *
 *   this function is similar to strcspn() but searches for one
 *   character instead of several; it is identical to function 
 *   cindex() declared in strlib.h;
 *
 *.  published 2003 by charles maier associates limited for internal use;
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  compiled for debian gnu/linux using gcc compiler;
 *
 *--------------------------------------------------------------------*/

#ifndef CHRINDEX_SOURCE
#define CHRINDEX_SOURCE

#include "../chrlib/chrlib.h"

size_t chrindex (register char const *string, register unsigned c)

{
   char const *sp;

#ifdef CMASSOC_SAFEMODE
   if (string == (char *) (0))
   {
      return (0);
   }
#endif

   for (sp = string; (*sp != (char) (0)) && (*sp != (char)(c)); sp++);

   return ((size_t) (sp - string));
}

#endif

