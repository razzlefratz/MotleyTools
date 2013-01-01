/*====================================================================*
 *
 *   ll.c - convert escaped newlines to long lines; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/cmassoc.h"
#include "../files/files.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/error.c"
#endif

#ifndef MAKEFILE
#include "../files/vfopen.c"
#include "../files/makepath.c"
#include "../files/splitpath.c"
#include "../files/mergepath.c"
#endif

/*====================================================================*
 *   
 *--------------------------------------------------------------------*/

#ifndef isblank
#define isblank(c) (((char)(c) == ' ') || ((char)(c) == '\t')) 
#endif 
#ifndef nobreak
#define nobreak(c) (((signed)(c) != EOF) || ((char)(c) == '\n')) 
#endif  

/*====================================================================*
 *
 *   void func (flag_t flags, FILE * ifp, FILE * ofp);
 *
 *   read from ifp and write to ofp; remove escaped newlines to form
 *   one long line from consecutive continuation lines; 
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void func (flag_t flags, FILE * ifp, FILE * ofp) 

{
	signed c;
	signed o;
	while ((c = getc (ifp)) != EOF) 
	{
		switch (c) 
		{
		case '/':
			o = getc (ifp);
			if (o == '*') 
			{
				putc (c, ofp);
				do 
				{
					ungetc (o, ifp);
					do 
					{
						o = getc (ifp);
						putc (o, ofp);
					}
					while ((o != EOF) && (o != '*'));
					o = getc (ifp);
				}
				while ((o != EOF) && (o != c));
				putc (c, ofp);
			}
			else if (o == '/') 
			{
				putc (c, ofp);
				do 
				{
					putc (c, ofp);
					c = getc (ifp);
				}
				while (nobreak ((char) (c)));
				putc ('\n', ofp);
			}
			else 
			{
				ungetc (o, ifp);
				putc (c, ofp);
			}
			break;
		case '\"':
		case '\'':
			putc (c, ofp);
			for (o = getc (ifp); (o != EOF) && (o != c); o = getc (ifp)) 
			{
				if ((c = putc (c, ofp)) == '\\') 
				{
					putc (c, ofp);
					if ((c = getc (ifp)) != EOF) 
					{
						putc (c, ofp);
					}
				}
			}
			putc (c, ofp);
			break;
		case '#':
			do 
			{
				putc (c, ofp);
				c = getc (ifp);
			}
			while (nobreak ((char) (c)));
			putc ('\n', ofp);
			break;
		case '\\':
			o = getc (ifp);
			switch (o) 
			{
			case '\r':
				o = getc (ifp);
				if (nobreak (o)) 
				{
					ungetc (o, ifp);
				}
			case '\n':
				do 
				{
					o = getc (ifp);
				}
				while (isblank (o));
				ungetc (o, ifp);
				break;
			case EOF:
				putc (c, ofp);
				break;
			default:
				putc (c, ofp);
				putc (o, ofp);
				break;
			}
			break;
		default:
			putc (c, ofp);
			break;
		}
	}
	return;
}


/*====================================================================*
 *   main program;
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"",
		PUTOPTV_S_FILTER,
		"convert escaped newlines to form long lines;",
		(char const *) (0)
	};
	flag_t flags = (flag_t) (0);
	signed c;
	while ((c = getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		default:
			break;
		}
	}
	argc -= optind;
	argv += optind;
	if (!argc) 
	{
		func (flags, stdin, stdout);
	}
	while ((argc) && (* argv)) 
	{
		if (vfopen (* argv)) 
		{
			func (flags, stdin, stdout);
		}
		argc--;
		argv++;
	}
	exit (0);
}

