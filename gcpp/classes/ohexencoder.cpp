/*====================================================================*
 *
 *   ohexencoder.cpp - implementation of the ohexencoder class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oHEXENCODER_SOURCE
#define oHEXENCODER_SOURCE

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ohexencoder.hpp"

/*====================================================================*
 *   constant definitions an declarations;
 *--------------------------------------------------------------------*/

char const ohexencoder::mdigit [] = "0123456789ABCDEF";

/*====================================================================*
 *
 *   char * decode(char *string);
 *
 *
 *--------------------------------------------------------------------*/

char *ohexencoder::decode (char *string) 

{
	char *target = string;

#ifdef CMASSOC_SAFEMODE

	if (!string) 
	{
		return (string);
	}

#endif

	while ((*target = *string) != (char) (0)) 
	{
		if (*string == '%') 
		{
			signed upper = oascii::todigit (string [1]);
			signed lower = oascii::todigit (string [2]);
			if ((upper == -1) || (lower == -1)) 
			{
				continue;
			}
			*target = (char) ((upper << 4) | lower);
			string++;
			string++;
		}
		target++;
		string++;
	}
	return (target);
}


/*====================================================================*
 *   
 *   ohexencoder ();
 *   
 *
 *--------------------------------------------------------------------*/

ohexencoder::ohexencoder () 

{
	return;
}


/*====================================================================*
 *   
 *   ~ohexencoder ();
 *   
 *   
 *--------------------------------------------------------------------*/

ohexencoder::~ohexencoder () 

{
	return;
}


/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#endif

