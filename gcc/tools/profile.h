/*====================================================================*
 *
 *   profile.h - 
 *
 *.  Motley Tools by Charles Maier
 *:  modified tue 16 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PROFILE_HEADER
#define PROFILE_HEADER

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

signed profilenumber(char const * profile, char const * section, char const * element, signed content);
char const * profilestring(char const * profile, char const * section, char const * element, char const * content);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif



