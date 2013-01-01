/*====================================================================*
 *
 *   config.h - configuration file definitions and declarations;
 *
 *   a configuration file contains named parts where each part may
 *   jave one or more named items where each has associated text;
 *
 *   the named file can be searched for the first occurance of 
 *   a named part then the first occurance of a named item; the
 *   associated text is returned, if preent;
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

signed confignumber (char const * file, char const * part, char const * item, signed text);
char const * configstring (char const * file, char const * part, char const * item, char const * text);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

