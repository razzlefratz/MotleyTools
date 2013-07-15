/*====================================================================*
 *
 *   html.c - print HTML page template;
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#define _GETOPT_H

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/version.h"
#include "../tools/profile.h"
#include "../tools/markup.h"
#include "../tools/format.h"
#include "../tools/error.h"
#include "../tools/types.h"
#include "../tools/sizes.h"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../tools/getoptv.c"
#include "../tools/putoptv.c"
#include "../tools/version.c"
#include "../tools/profile.c"
#include "../tools/totruth.c"
#include "../tools/indent.c"
#include "../tools/error.c"
#include "../tools/efreopen.c"
#endif

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define HTML_PROFILE "/etc/html.ini"
#define HTML_SECTION "default"

/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/

static char const * subject = HTML_SUBJECT; 
static char const * contact = HTML_AUTHOR; 
static char const * cssfile = CSS_STYLESHEET; 
static char const * charset = ISO_CHARSET; 

/*====================================================================*
 *
 *   unsigned links (unsigned margin, char const * style);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static unsigned links (unsigned margin, char const * style) 

{ 
	indent (margin++, "<div class='%s'>", style); 
	indent (margin, "[<a href='%s' title='%s'>%s</a>]", HTML_PATH, HTML_NAME, HTML_PREV); 
	indent (margin, "[<a href='%s' title='%s'>%s</a>]", HTML_PATH, HTML_NAME, HTML_HOME); 
	indent (margin, "[<a href='%s' title='%s'>%s</a>]", HTML_PATH, HTML_NAME, HTML_NEXT); 
	indent (margin--, "</div>"); 
	return (margin); 
} 

/*====================================================================*
 *
 *   unsigned header (unsigned margin);
 *
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static unsigned header (unsigned margin) 

{ 
	extern char const * contact; 
	extern char const * subject; 
	extern char const * cssfile; 
	extern char const * charset; 
	indent (margin++, "<html>"); 
	indent (margin++, "<head>"); 
	indent (margin++, "<title>"); 
	indent (margin, "%s", subject); 
	indent (margin--, "</title>"); 
	indent (margin, "<meta http-equiv='content-type' content='%s;%s'/>", ISO_CONTENT, charset); 
	indent (margin, "<meta name='author' content='%s'/>", contact); 
	indent (margin, "<meta name='generator' content='%s'/>", HTML_PROGRAM); 
	indent (margin, "<meta name='robots' content='%s'/>", HTML_ROBOTS); 
	indent (margin, "<link rel='stylesheet' href='%s' type='%s'/>", cssfile, CSS_CONTENT); 
	indent (margin++, "<style type='text/css'>"); 
	indent (margin--, "</style>"); 
	indent (margin--, "</head>"); 
	indent (margin++, "<body class='%s'>", "standard"); 
	margin = links (margin, STYLE_TOPLINK); 
	indent (margin++, "<h1>"); 
	indent (margin, "%s", subject); 
	indent (margin--, "</h1>"); 
	indent (margin, "<!-- BEGIN CONTENT -->"); 
	return (margin); 
} 

/*====================================================================*
 *
 *   unsigned body (unsigned margin);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static unsigned body (unsigned margin) 

{ 
	signed c; 
	while ((c = getc (stdin)) != EOF) 
	{ 
		putc (c, stdout); 
	} 
	return (margin); 
} 

/*====================================================================*
 *
 *   unsigned footer (unsigned margin);
 *
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

static unsigned footer (unsigned margin) 

{ 
	indent (margin, "<!-- END CONTENT -->"); 
	margin = links (margin, STYLE_BOTLINK); 
	indent (margin--, "</body>"); 
	indent (margin--, "</html>"); 
	return (margin); 
} 

/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{ 
	extern char const * subject; 
	extern char const * contact; 
	extern char const * cssfile; 
	static char const * optv [] = 
	{ 
		"op:s:", 
		PUTOPTV_S_FUNNEL, 
		"print HTML page template", 
		"o\tprint default profile on stdout", 
		"p f\tuse profile (s) [" HTML_PROFILE "]", 
		"s s\tuse profile section (s) [" HTML_SECTION "]", 
		(char const *)(0)
	}; 
	char const * profile = HTML_PROFILE; 
	char const * section = HTML_SECTION; 
	unsigned margin = 0; 
	signed c; 
	while ((c = getoptv (argc, argv, optv)) != - 1) 
	{ 
		switch (c) 
		{ 
		case 'o': 
			printf ("[%s]\n", section); 
			printf ("subject=%s\n", subject); 
			printf ("contact=%s\n", contact); 
			printf ("cssfile=%s\n", cssfile); 
			printf ("charset=%s\n", charset); 
			return (0); 
		case 'p': 
			profile = optarg; 
			break; 
		case 's': 
			section = optarg; 
			break; 
		default: 
			break; 
		} 
	} 
	argc -= optind; 
	argv += optind; 
	subject = profilestring (profile, section, "subject", subject); 
	contact = profilestring (profile, section, "contact", contact); 
	cssfile = profilestring (profile, section, "cssfile", cssfile); 
	charset = profilestring (profile, section, "charset", charset); 
	margin = header (margin); 
	if (!argc) 
	{ 
		margin = body (margin); 
	} 
	while ((argc) && (* argv)) 
	{ 
		if (efreopen (* argv, "rb", stdin)) 
		{ 
			margin = body (margin); 
		} 
		argc--; 
		argv++; 
	} 
	margin = footer (margin); 
	return (0); 
} 

