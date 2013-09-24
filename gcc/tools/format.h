/*====================================================================*
 *
 *   format.h - 
 *
 *.  Motley Tools by Charles Maier
 *:  modified tue 16 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FORMAT_HEADER
#define FORMAT_HEADER

/*====================================================================*
 *   character and string constants;
 *--------------------------------------------------------------------*/

#define CSPACE (' ')
#define CUPPER ('=')
#define CLOWER ('-')
#define CCTRLR ('@')

/*====================================================================*
 *   wildcard pattern matching; 
 *--------------------------------------------------------------------*/

#define MATCH_C_MASK '?'
#define MATCH_C_WILD '*'

/*====================================================================*
 *   symbolic names for some generic command delimiters; 
 *--------------------------------------------------------------------*/

#define ITEM_C_EXTENDER (':')
#define ITEM_S_EXTENDER (":")
#define LIST_C_EXTENDER (';')
#define LIST_S_EXTENDER (";")

#define TOOLS_B_NUMBER (1 << 0)
#define TOOLS_B_DEFINE (1 << 1)
#define TOOLS_B_DECLARE (1 << 2)
#define TOOLS_B_SWITCH (1 << 3)
#define TOOLS_B_MARKUP (1 << 4)
#define TOOLS_B_NORMAL (TOOLS_B_DEFINE|TOOLS_B_DECLARE|TOOLS_B_SWITCH|TOOLS_B_MARKUP)

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

#ifdef __GNUC__

__attribute__ ((format(printf, 3, 4))) 

#endif

void fdprint(signed device, signed margin, char const * format, ...);

#ifdef __GNUC__

__attribute__ ((format(printf, 2, 3))) 

#endif

void indent(signed margin, char const * format, ...);

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

void breakout(char const * string, size_t length);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif



