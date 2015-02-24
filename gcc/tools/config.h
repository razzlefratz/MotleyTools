/*====================================================================*
 *
 *   config.h - configuration file definitions and declarations;
 *
 *   configuration files contain named parts where each part may 
 *   have one of more named items that have text definitions; 
 *
 *   the named file can be searched for the first occurance of a
 *   named part then the first occurance of a named item; return
 *   the associated text, if present;
 *
 *   [part1]
 *   item1=text
 *   item2=text
 *
 *   [part2]
 *   item1=text
 *   item2=text
 *
 *--------------------------------------------------------------------*/

#ifndef CONFIG_HEADER
#define CONFIG_HEADER

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

signed confignumber(char const * file, char const * part, char const * item, signed text);
char const * configstring(char const * file, char const * part, char const * item, char const * text);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif



