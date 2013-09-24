/*====================================================================*
 *
 *   profile.c - microsoft style profile read/write functions;
 *
 *   provide an alternative to the Microsoft PrivateProfile concept;
 *
 *   a profile is a configuration file that contains named sections 
 *   where each section may contain one of more named elements that
 *   have string definitions; 
 *
 *   the named profile can be searched for the first occurance of 
 *   a named section then the first occurance of a named element;
 *
 *   [section1]
 *   element1=string
 *   element2=string
 *
 *   [section2]
 *   element1=string
 *   element2=string
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PROFILE_SOURCE
#define PROFILE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/profile.h"
#include "../tools/number.h"
#include "../tools/types.h"
#include "../tools/chars.h"

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static char buffer[1024] = "";
static signed c;

/*====================================================================*
 *
 *   void _newchar (FILE * fp);
 *
 *   read and discard spaces and tabs;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void _newchar(FILE * fp)

{
	do 
	{
		c = getc(fp);
	}
	while (isblank(c));
	return;
}

/*====================================================================*
 *
 *   void _newline (FILE * fp);
 *
 *   read and discard characters until end-of-line or end-of-file 
 *   is detected; read the first character of next line if end of 
 *   file has not been detected;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void _newline(FILE * fp)

{
	while (nobreak(c))
	{
		c = getc(fp);
	}
	_newchar (fp);
	return;
}

/*====================================================================*
 *
 *   bool compare (FILE * fp, char const *sp);
 *
 *   compare file characters to text characters until they differ 
 *   or until the text, line or file ends; a match occurs if the 
 *   text ends before the line or file ends;
 *
 *   embedded file or string sp may contain any character except the explicit delimiter 
 *   and linefeed; spaces and tabs found with the sp read from
 *   file are ignored;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static bool compare(FILE * fp, char const * sp)

{
	while (isblank(* sp))
	{
		sp++;
	}
	while ((* sp) && (toupper(c) == toupper(* sp)) && nobreak(c))
	{
		do 
		{
			sp++;
		}
		while (isblank(* sp));
		_newchar (fp);
	}
	return (! * sp);
}

/*====================================================================*
 *
 *   void _collect (FILE * fp);
 *
 *   collect text to end of line; remove leading and trailing space
 *   but preserve embedded space; replace escape sequences;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void _collect(FILE * fp)

{
	char * bp = buffer;
	char * cp = buffer;
	while ((c != ';') && nobreak(c))
	{
		if (c == '\\')
		{
			c = getc(fp);
			if (c == 'n')
			{
				c = '\n';
			}
			if (c == 't')
			{
				c = '\t';
			}
		}
		if ((size_t) (cp - buffer) < (sizeof(buffer) - 1))
		{
			* cp++ = c;
		}
		if (! isspace(c))
		{
			bp = cp;
		}
		c = getc(fp);
	}
	* bp = (char)(0);
	return;
}

/*====================================================================*
 *
 *   char const * profilestring (char const * profile, char const * section, char const * element, char const * content)
 *
 *   profile.h
 *
 *   open the named profile, locate the named section and return the 
 *   named element string, if present; return an alternative string 
 *   if the section or element is missing; 
 *
 *   this function always returns a string;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * profilestring(char const * profile, char const * section, char const * element, char const * content)

{
	FILE * fp;

#if CMASSOC_SAFEMODE

	if (! profile)
	{
		return (content);
	}
	if (! section)
	{
		return (content);
	}
	if (! element)
	{
		return (content);
	}

#endif

	if ((fp = fopen(profile, "rb")))
	{
		for (_newchar(fp); c != EOF; _newline(fp))
		{
			if (c != '[')
			{
				continue;
			}
			_newchar (fp);
			if (! compare(fp, section))
			{
				continue;
			}
			if (c != ']')
			{
				continue;
			}
			for (_newline(fp); (c != '[') && (c != EOF); _newline(fp))
			{
				if (c == ';')
				{
					continue;
				}
				if (! compare(fp, element))
				{
					continue;
				}
				if (c != '=')
				{
					continue;
				}
				_newchar (fp);
				_collect (fp);
				content = strdup(buffer);
				break;
			}
			break;
		}
		fclose (fp);
	}
	return (content);
}

/*====================================================================*
 *
 *   signed profilenumber (char const * profile, char const * section, char const * element, signed content);
 *
 *   profile.h
 *
 *   open the named profile, locate the named section and return the
 *   named element string as a signed integer, if present; return an
 *   alternative integer if the section or element is missing; 
 *
 *   this function always returns a signed integer; boolean strings
 *   like "on", "off", "true" and "false" are converted to integers
 *   via table lookup;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed profilenumber(char const * profile, char const * section, char const * element, signed content)

{
	char const * string = profilestring(profile, section, element, "");
	signed integer = totruth(string);
	if (integer == - 1)
	{
		signed sign = 1;
		if (* string == '+')
		{
			string++;
		}
		else if(* string == '-')
		{
			sign = - sign;
			string++;
		}
		for (integer = 0; isdigit(* string); string++)
		{
			integer *= 10;
			integer += * string - '0';
		}
		if (* string)
		{
			return (content);
		}
		integer *= sign;
	}
	return (integer);
}

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *   demo/test program; arguments are profile, section, element and content in 
 *   that order; you can construct your own configuration profile and
 *   observe behaviour; 
 *
 *--------------------------------------------------------------------*/

#if 0

#include <stdio.h>
#include "../tools/totruth.c"

int main(int argc, char const * argv[])

{
	char const * content = proprofilecontent(argv[1], argv[2], argv[3], argv[4]);
	printf ("profile=[%s] section=[%s] element=[%s] content=[%s]\n", argv[1], argv[2], argv[3], content);
	return (0);
}

#endif

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *   demo/test program; arguments are profile, section, element and content in 
 *   that order; you can construct your own configuration profile and
 *   observe behaviour; 
 *
 *--------------------------------------------------------------------*/

#if 0

#include <stdio.h>
#include "../tools/totruth.c"

int main(int argc, char const * argv[])

{
	signed content = profilenumber(argv[1], argv[2], argv[3], atoi(argv[4]));
	printf ("profile=[%s] section=[%s] element=[%s] content=[%d]\n", argv[1], argv[2], argv[3], content);
	return (0);
}

#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



