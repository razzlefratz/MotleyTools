/*====================================================================*
 *
 *   void copyquote (SCAN * content, char buffer [], signed length);
 *
 *   scan.h
 *
 *   copy the current token to a user supplied buffer of specified 
 *   length; the token is assumed to be enclosed in quotes of some
 *   kind which are discarded before the token is copied;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef COPYQUOTE_SOURCE
#define COPYQUOTE_SOURCE

# include "../scan/scan.h"

void copyquote (SCAN * content, char buffer [], signed length) 

{
	content->first++;
	content->final--;
	copytoken (content, buffer, length);
	content->first--;
	content->final++;
	return;
}


#endif

