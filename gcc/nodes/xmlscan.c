/*====================================================================*
 *
 *   xmlscan.c - 
 *
 *   nodes.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef XMLSCAN_SOURCE
#define XMLSCAN_SOURCE

/*====================================================================*
 *  system header files;
 *--------------------------------------------------------------------*/

#include <string.h>
#include <ctype.h>

/*====================================================================*
 *  custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/error.h"
#include "../tools/chars.h"
#include "../strlib/strlib.h"
#include "../nodes/nodes.h"

/*====================================================================*
 *
 *   char * advance (char * string, unsigned * lineno);
 *
 *   discard whitespace and count newlines up to the next character; 
 *
 *   this function is critical to the XML parsing engine because it
 *   ensures that substrings are NUL terminated and line counts are
 *   accurate;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static char * advance (char * string, unsigned * lineno) 

{
	while (isspace (*string)) 
	{
		if (*string == '\n') 
		{
			(*lineno)++;
		}
		*string++ = (char)(0);
	}
	return (string);
}


/*====================================================================*
 *
 *   char * discard (char * string, unsigned * lineno);
 *
 *   erase current character; advance to next non-blank character;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static char * discard (char * string, unsigned * lineno) 

{
	*string++ = (char)(0);
	string = advance (string, lineno);
	return (string);
}


/*====================================================================*
 *
 *   char * nmtoken (char * string, unsigned * lineno);
 *
 *   span nmtoken as per w3c xml 1.0 specification;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static char * nmtoken (char * string, unsigned * lineno) 

{
	while (isalnum (*string) || (*string == ':') || (*string == '.') || (*string == '-') || (*string == '_')) 
	{
		string++;
	}
	return (string);
}


/*====================================================================*
 *
 *   char * unknown (char * string, unsigned * lineno);
 *
 *   span unknown entity;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static char * unknown (char * string, unsigned * lineno) 

{
	while ((*string) && !isspace (*string) && !strchr ("<=/?>", *string)) 
	{
		string++;
	}
	return (string);
}


/*====================================================================*
 *
 *   static char * comment (char * string, unsigned * line);
 *
 *   span comment as per w3c xml 1.0 specification;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static char * comment (char * string, unsigned * lineno) 

{
	string++;
	if (*string == '-') 
	{
		while (*string == '-') 
		{
			string++;
		}
		while ((*string) && (*string != '-')) 
		{
			while ((*string) && (*string != '-')) 
			{
				if (*string == '\n') 
				{
					(*lineno)++;
				}
				string++;
			}
			string++;
		}
		while (*string == '-') 
		{
			string++;
		}
	}
	return (string);
}


/*====================================================================*
 *
 *   char * extract (char * string, unsigned * lineno, char quote);
 *
 *   span literal string excluding quotes;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static char * extract (char *string, unsigned * lineno, char quote) 

{
	if (*string == quote) 
	{
		*string++ = (char)(0);
	}
	while ((*string) && (*string != quote)) 
	{
		if (*string == '\n') 
		{
			(*lineno)++;
		}
		string++;
	}
	if (*string == quote) 
	{
		*string++ = (char)(0);
	}
	return (string);
}


/*====================================================================*
 *
 *   char * literal (char * string, unsigned * lineno, char quote);
 *
 *   span literal string including quotes;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static char * literal (char *string, unsigned * lineno, char quote) 

{
	if (*string == quote) 
	{
		string++;
	}
	while ((*string) && (*string != quote)) 
	{
		if (*string == '\n') 
		{
			(*lineno)++;
		}
		string++;
	}
	if (*string == quote) 
	{
		string++;
	}
	return (string);
}


/*====================================================================*
 *
 *   char * context (char * string, unsigned *lineno, char final);
 *
 *   span current context; preserve delimiters and whitespace; count 
 *   newlines;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static char * context (char *string, unsigned * lineno, char final) 

{
	if (*string) 
	{
		string++;
	}
	while ((*string) && (*string != final)) 
	{
		if (*string == '{') 
		{
			string = context (string, lineno, '}');
			continue;
		}
		if (*string == '(') 
		{
			string = context (string, lineno, ')');
			continue;
		}
		if (*string == '[') 
		{
			string = context (string, lineno, ']');
			continue;
		}
		if (isquote (*string)) 
		{
			string = literal (string, lineno, *string);
			continue;
		}
		if (*string == '\n') 
		{
			(*lineno)++;
		}
		string++;
	}
	if (*string) 
	{
		string++;
	}
	return (string);
}


/*====================================================================*
 *
 *   char * compact (char * string, unsigned * lineno, char final);
 *
 *   collect and compress content as per w3c xml 1.0 specification;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static char * compact (char *string, unsigned * lineno, char final) 

{
	signed space = 0;
	char * output = string;
	while ((*string) && (*string != final)) 
	{
		if (isspace (*string)) 
		{
			string = advance (string, lineno);
			space = 1;
			continue;
		}
		if (space) 
		{
			*output++ = ' ';
			space = 0;
			continue;
		}
		*output++ = *string++;
	}
	if (output < string) 
	{
		*output = (char)(0);
	}
	return (string);
}


/*====================================================================*
 *
 *   char * collect (char * string, unsigned *lineno, char final);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static char * collect (char *string, unsigned * lineno, char final) 

{
	while ((*string) && (*string != final)) 
	{
		if (*string == '\n') 
		{
			(*lineno)++;
		}
		string++;
	}
	return (string);
}


/*====================================================================*
 *
 *   unsigned trace (NODE * node);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#if NODE_PATH

static unsigned trace (NODE * node) 

{
	if ((node) && (node->above)) 
	{
		unsigned level = trace (node->above);
		unsigned count = level;
		printf ("%03d ", node->line);
		while (count--) 
		{
			putc ('|', stdout);
			putc (' ', stdout);
		}
		printf ("%s\n", node->text);
		return (level+1);
	}
	return (0);
}


#endif

/*====================================================================*
 *
 *   void xmlscan (NODE * node);
 *
 *   scan node->text for XML and create a hierarchial string vector to
 *   reflect document structure; replace whitespace and punctuation in
 *   node->text with NUL sub-string delimiters; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void xmlscan (NODE * node) 

{
	NODE * section = node;
	NODE * segment;
	NODE * element;
	NODE * attribute;
	NODE * value;
	char * string = node->text;
	char prefix = (char)(0);
	char suffix = (char)(0);
	unsigned lineno = 1;
	if (!section) 
	{
		error (1, EFAULT, "section is null");
	}
	if (!string) 
	{
		error (1, EFAULT, "content is null");
	}
	string = advance (string, &lineno);
	while (*string) 
	{
		if (*string == '<') 
		{
			prefix = '<';
			suffix = '>';
			string = discard (string, &lineno);
			if ((*string == '%') || (*string == '?')) 
			{
				prefix = *string;
			}
			else if (*string == '!') 
			{
				prefix = *string;
				string = discard (string, &lineno);
			}
			else if (*string == '/') 
			{
				prefix = *string;
				string = discard (string, &lineno);
			}
			element = xmlnode (section);
			element->line = lineno;
			element->type = NODE_ELEM;
			element->text = string;
			if ((prefix == '%') || (prefix == '?')) 
			{
				while ((*string) && (*string != '>')) 
				{
					string = collect (string, &lineno, prefix);
					string++;
				}
			}
			else if (isalpha (*string)) 
			{
				string = nmtoken (string, &lineno);
			}
			else if (*string == '-') 
			{
				string = comment (string, &lineno);
			}
			else if (*string == '[') 
			{
				string = context (string, &lineno, ']');
			}
			else 
			{
				string = unknown (string, &lineno);
			}
			string = advance (string, &lineno);
			while ((*string) && (*string != '<') && (*string != '/') && (*string != '>')) 
			{
				attribute = xmlnode (element);
				attribute->type = NODE_ATTR;
				attribute->line = lineno;
				attribute->text = string;
				if (isalpha (*string)) 
				{
					string = nmtoken (string, &lineno);
				}
				else if (*string == '-') 
				{
					string = comment (string, &lineno);
				}
				else if (*string == '[') 
				{
					string = context (string, &lineno, ']');
				}
				else if (isquote (*string)) 
				{
					string = literal (string, &lineno, *string);
				}
				else 
				{
					string = unknown (string, &lineno);
				}
				string = advance (string, &lineno);
				if (*string == '=') 
				{
					string = discard (string, &lineno);
					value = xmlnode (attribute);
					value->type = NODE_VALU;
					value->line = lineno;
					value->text = string;
					if (isquote (*string)) 
					{
						string = extract (string, &lineno, *string);
						value->text++;
					}
					else 
					{
						string = unknown (string, &lineno);
					}
					string = advance (string, &lineno);
				}
			}
			if (*string == '/') 
			{
				suffix = *string;
				string = discard (string, &lineno);
			}
		}
		else if (*string == '>') 
		{
			string = discard (string, &lineno);
			if (prefix == '!') 
			{
				element->type = NODE_SGML;
			}
			else if (prefix == '?') 
			{
				element->type = NODE_PROC;
			}
			else if (prefix == '%') 
			{
				element->type = NODE_CODE;
			}
			else if (prefix == '/') 
			{
				element->type = NODE_ETAG;
				if (element->below) 
				{
					error (1, 0, "Element </%s> on line %d has attributes or content.", element->text, element->line);
				}
				if (strcmp (section->text, element->text)) 
				{
					error (1, 0, "Element <%s> on line %d terminated by </%s> on line %d", section->text, section->line, element->text, element->line);
				}
				if (section->above) 
				{
					section = section->above;
				}
			}
			else if (suffix == '/') 
			{

#if 0

/*
 *	insert end tag for empty elements; this action can simplify tree traversal in some cases and
 *      complicate it in other cases; inserting an end tag is asthetically pleasing;
 */

				NODE * correct = xmlnode (element);
				correct->type = NODE_ETAG;
				correct->line = lineno;
				correct->text = element->text;

#endif

			}
			else 
			{
				section = element;
			}
		}
		else 
		{
			segment = xmlnode (section);
			segment->type = NODE_DATA;
			segment->line = lineno;
			segment->text = string;
			string = compact (string, &lineno, '<');
		}
	}
	return;
}


#endif

