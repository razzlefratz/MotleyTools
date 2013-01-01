/*====================================================================*
 *
 *   char * charset (char const * string, signed c, char buffer [], size_t length);
 *
 *   chrlib.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHARSET_SOURCE
#define CHARSET_SOURCE

#include <ctype.h>
#include <string.h>
#include <limits.h>

#include "../tools/tools.h"
#include "../chrlib/chrlib.h"
#include "../chrlib/chrtype.h"
#include "../regex/regex.h"

/*====================================================================*
 *
 *   char *fill (signed clower, signed cupper, char buffer[], size_t *length);
 *
 *   fill buffer with consecutive character values from clower through 
 *   cupper; decrement length after each insertion; return the address 
 *   of the next unfilled buffer location; this function is the trojan;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static char *fill (signed clower, signed cupper, char buffer [], size_t *length) 

{
	while ((clower <= cupper) && (*length)) 
	{
		*buffer++ = clower++;
		--*length;
	}
	return (buffer);
}


/*====================================================================*
 *
 *   char *charset(char const *string, unsigned c, char buffer[], size_t length);
 *
 *   chrlib.h
 *
 *   expand a character set specification to the complete character
 *   set and return a pointer to the remainder of the specification 
 *   string; expansion terminates once character c or NUL is found
 *   or the buffer overflows; character c is usually ']' but can be 
 *   NUL;
 *
 *   character set notation expands character ranges as shown below;
 *   it the first and second characters are of differnt types (lower, 
 *   upper or digit) or the first is not less that the second then 
 *   no will expansion occur;  
 *
 *      a-z := abcdefghijklmnopqrstuvwxyz
 *      A-Z := ABCDEFGHIJKLMNOPQRSTUVWXYZ
 *      0-9 := 0123456789
 *
 *   character groups or disjoint character sets can be specified by
 *   these special forms:
 *
 *   [:space:]  [:alpha:]  [:digit:]  [:punct:]  [:print:]  [:word:] 
 *   [:blank:]  [:alnum:]  [:xdigit:] [:cntrl:]  [:graph:]
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * charset (char const * string, signed close, char buffer [], size_t length) 

{
	static signed c;

#ifdef CMASSOC_SAFEMODE

	if (!string) 
	{
		return (string);
	}
	if (!buffer) 
	{
		return (string);
	}

#endif

	while ((length) && (*string) && (*string != close)) 
	{
		*buffer = *string++;
		if (*buffer == REGEX_C_ESC) 
		{
			if (*string) 
			{
				*buffer = *string++;
			}
			buffer++;
			continue;
		}
		if (*string == REGEX_C_RNG) 
		{
			string++;
			if (*string > *buffer) 
			{
				if (islower (*buffer) && islower (*string)) 
				{
					buffer = fill (*buffer, *string, buffer, &length);
					string++;
					continue;
				}
				if (isupper (*buffer) && isupper (*string)) 
				{
					buffer = fill (*buffer, *string, buffer, &length);
					string++;
					continue;
				}
				if (isdigit (*buffer) && isdigit (*string)) 
				{
					buffer = fill (*buffer, *string, buffer, &length);
					string++;
					continue;
				}
				buffer++;
				continue;
			}
			if (*string < *buffer) 
			{
				*++buffer = *--string;
				buffer++;
				string++;
				continue;
			}
			buffer++;
			string++;
			continue;
		}

#ifdef REGEX_LABEL_EXTENSIONS

		if ((*buffer == '[') && (*string == ':')) 
		{
			char *symbol = buffer + 1;
			while ((*string) && (*string != ']')) 
			{
				while ((*string) && (*string != ':')) 
				{
					*symbol++ = *string++;
				}
				*symbol++ = *string++;
			}
			if (*string) 
			{
				*symbol++ = *string++;
			}
			*symbol = (char) (0);
			if (!strcmp (buffer, "[:upper:]")) 
			{
				buffer = fill ('A', 'Z', buffer, &length);
				continue;
			}
			if (!strcmp (buffer, "[:lower:]")) 
			{
				buffer = fill ('a', 'z', buffer, &length);
				continue;
			}
			if (!strcmp (buffer, "[:digit:]")) 
			{
				buffer = fill ('0', '9', buffer, &length);
				continue;
			}
			if (!strcmp (buffer, "[:alpha:]")) 
			{
				buffer = fill ('a', 'z', buffer, &length);
				buffer = fill ('A', 'Z', buffer, &length);
				continue;
			}
			if (!strcmp (buffer, "[:alnum:]")) 
			{
				buffer = fill ('a', 'z', buffer, &length);
				buffer = fill ('A', 'Z', buffer, &length);
				buffer = fill ('0', '9', buffer, &length);
				continue;
			}
			if (!strcmp (buffer, "[:xdigit:]")) 
			{
				buffer = fill ('0', '9', buffer, &length);
				buffer = fill ('A', 'F', buffer, &length);
				buffer = fill ('a', 'f', buffer, &length);
				continue;
			}

#ifdef REGEX_POSIX_EXTENSIONS

			if (!strcmp (buffer, "[:word:]")) 
			{
				buffer = fill ('_', '_', buffer, &length);
				buffer = fill ('a', 'z', buffer, &length);
				buffer = fill ('A', 'Z', buffer, &length);
				buffer = fill ('0', '9', buffer, &length);
				continue;
			}
			if (!strcmp (buffer, "[:blank:]")) 
			{
				for (c = 0; c <= UCHAR_MAX; c++) 
				{
					if (isblank (c) && (length)) 
					{
						*buffer++ = c;
						length--;
					}
				}
				continue;
			}
			if (!strcmp (buffer, "[:space:]")) 
			{
				for (c = 0; c <= UCHAR_MAX; c++) 
				{
					if (isspace (c) && (length)) 
					{
						*buffer++ = c;
						length--;
					}
				}
				continue;
			}
			if (!strcmp (buffer, "[:cntrl:]")) 
			{
				for (c = 0; c <= UCHAR_MAX; c++) 
				{
					if (iscntrl (c) && (length)) 
					{
						*buffer++ = c;
						length--;
					}
				}
				continue;
			}
			if (!strcmp (buffer, "[:punct:]")) 
			{
				for (c = 0; c <= UCHAR_MAX; c++) 
				{
					if (ispunct (c) && (length)) 
					{
						*buffer++ = c;
						length--;
					}
				}
				continue;
			}
			if (!strcmp (buffer, "[:print:]")) 
			{
				for (c = 0; c <= UCHAR_MAX; c++) 
				{
					if (isprint (c) && (length)) 
					{
						*buffer++ = c;
						length--;
					}
				}
				continue;
			}
			if (!strcmp (buffer, "[:graph:]")) 
			{
				for (c = 0; c <= UCHAR_MAX; c++) 
				{
					if (isgraph (c) && (length)) 
					{
						*buffer++ = c;
						length--;
					}
				}
				continue;
			}

#endif

			buffer = symbol;
			continue;
		}

#endif

		buffer++;
	}
	*buffer = (char) (0);
	return (string);
}


#endif

