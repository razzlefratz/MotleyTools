/*====================================================================*
 *
 *   config.c - configuration file reader;
 *
 *   configuration files contain named parts where each part may 
 *   contain one of more named items that have text definitions; 
 *
 *   the named file can be searched for the first occurance of a
 *   named part then the first occurance of a named item; 
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

#ifndef CONFIG_SOURCE
#define CONFIG_SOURCE

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

#include "../tools/config.h"
#include "../tools/types.h"
#include "../tools/chars.h"

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static char buffer [1024] = "";
static signed c;

/*====================================================================*
 *
 *   bool compare (FILE * fp, char const *sp);
 *
 *   compare file and text characters until they differ or until end
 *   of text, line or file occurs; a match is declared when the text 
 *   ends before the line or file;
 *
 *   spaces and tabs within the argument string or file string are
 *   ignored such that "item1", " item1 " and "item 1" all match;
 *
 *--------------------------------------------------------------------*/

static bool compare (FILE * fp, char const * sp) 

{
	while (isblank (*sp)) 
	{
		sp++;
	}
	while ((*sp) && (toupper (c) == toupper (*sp)) && nobreak (c)) 
	{
		do 
		{
			sp++;
		}
		while (isblank (*sp));
		do 
		{
			c = getc (fp);
		}
		while (isblank (c));
	}
	return (!*sp);
}


/*====================================================================*
 *
 *   void collect (FILE * fp);
 *
 *   collect text to end-of-line; remove leading and trailing space
 *   but preserve embedded space; replace selected escape sequences;
 *
 *--------------------------------------------------------------------*/

static void collect (FILE * fp) 

{
	char *bp = buffer;
	char *cp = buffer;
	while ((c != ';') && nobreak (c)) 
	{
		if (c == '\\') 
		{
			c = getc (fp);
			if (c == 'n') 
			{
				c = '\n';
			}
			if (c == 't') 
			{
				c = '\t';
			}
		}
		if ((size_t)(cp - buffer) < (sizeof (buffer) - 1)) 
		{
			*cp++ = c;
		}
		if (!isspace (c)) 
		{
			bp = cp;
		}
		c = getc (fp);
	}
	*bp = '\0';
	return;
}


/*====================================================================*
 *
 *   void discard (FILE * fp);
 *
 *   read and discard characters until end-of-line or end-of-file 
 *   is detected then read the first character of next line;
 *
 *--------------------------------------------------------------------*/

static void discard (FILE * fp) 

{
	while (nobreak (c)) 
	{
		c = getc (fp);
	}
	if (c != EOF) 
	{
		c = getc (fp);
	}
	return;
}


/*====================================================================*
 *
 *   Const char * configstring (char const * file, char const * part, char const * item, char const * text)
 *
 *   open the named file, find the named part and return the named       
 *   item text; return alternative text when the file part or item 
 *   is missing; the calling function must preserve returned text
 *   since it is over-written on successive calls;            
 *
 *--------------------------------------------------------------------*/

char const * configstring (char const * file, char const * part, char const * item, char const * text) 

{
	FILE *fp;
	if ((!file) || (!part) || (!item)) 
	{
		return (text);
	}
	if ((fp = fopen (file, "rb"))) 
	{
		for (c = getc (fp); c != EOF; discard (fp)) 
		{
			while (isblank (c)) 
			{
				c = getc (fp);
			}
			if (c != '[') 
			{
				continue;
			}
			do 
			{
				c = getc (fp);
			}
			while (isblank (c));
			if (!compare (fp, part)) 
			{
				continue;
			}
			if (c != ']') 
			{
				continue;
			}
			for (discard (fp); (c != '[') && (c != EOF); discard (fp)) 
			{
				while (isblank (c)) 
				{
					c = getc (fp);
				}
				if (c == ';') 
				{
					continue;
				}
				if (!compare (fp, item)) 
				{
					continue;
				}
				if (c != '=') 
				{
					continue;
				}
				do 
				{
					c = getc (fp);
				}
				while (isblank (c));
				collect (fp);
				text = buffer;
				break;
			}
			break;
		}
		fclose (fp);
	}
	return (text);
}


/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *   demo/test program; arguments are file, part, item and text in 
 *   that order; construct your own configuration file and observe
 *   behavior; 
 *
 *--------------------------------------------------------------------*/

#if 0

#include <stdio.h>

int main (int argc, char const * argv []) 

{
	char const * text = configstring (argv [1], argv [2], argv [3], argv [4]);
	printf ("file=[%s] part=[%s] item=[%s] text=[%s]\n", argv [1], argv [2], argv [3], text);
	return (0);
}


#endif

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

