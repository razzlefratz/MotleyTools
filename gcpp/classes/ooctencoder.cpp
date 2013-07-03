/*====================================================================*
 *
 *   ooctencoder.cpp - implementation of the ooctencoder class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oOCTENCODER_SOURCE
#define oOCTENCODER_SOURCE

/*====================================================================*
 *   standard source files;
 *--------------------------------------------------------------------*/

#include "../classes/ooctencoder.hpp"

/*====================================================================*
 *   constant definitions and declarations;
 *--------------------------------------------------------------------*/

char const ooctencoder::mdigit [] = "01234567";

/*====================================================================*
 *
 *   char * decode(char *string);
 *
 *
 *--------------------------------------------------------------------*/

char * ooctencoder::decode (char * string) 

{
	char * target = string;
	if (string) 
	{
		while ((* target = * string) != (char) (0)) 
		{
			if (* string == '\\') 
			{
				unsigned m,
				n,
				o;
				if ((m = chrindex (ooctencoder::mdigit, string [1])) > 0x0003) 
				{
					continue;
				}
				if ((n = chrindex (ooctencoder::mdigit, string [2])) > 0x0007) 
				{
					continue;
				}
				if ((o = chrindex (ooctencoder::mdigit, string [3])) > 0x0007) 
				{
					continue;
				}
				* target = (char) ((m << 6) + (n << 3) + (o << 0));
				string+= 3;
			}
			target++;
			string++;
		}
	}
	return (string);
}

/*====================================================================*
 *
 *   ooctencoder ();
 *   
 *   
 *--------------------------------------------------------------------*/

ooctencoder::ooctencoder () 

{
	return;
}

/*====================================================================*
 *
 *   ~ooctencoder ();
 *   
 *   
 *--------------------------------------------------------------------*/

ooctencoder::~ooctencoder () 

{
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

