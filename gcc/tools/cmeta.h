/*====================================================================*
 *
 *   cmeta.h - meta character definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CMETA_HEADER
#define CMETA_HEADER

/*====================================================================*
 *   wildcard pattern meta chaaracters;
 *--------------------------------------------------------------------*/

#define MATCH_C_MASK    ('?')
#define MATCH_C_WILD    ('*')

/*====================================================================*
 *   macro pre-processor meta characters
 *--------------------------------------------------------------------*/

#define MACRO_C_ARG       ('$')
#define MACRO_C_NIL       ('|')
#define MACRO_C_COMMAND   ('#')
#define MACRO_C_CONTINUE  ('\\')
#define MACRO_C_EXTEND    ('-')

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

