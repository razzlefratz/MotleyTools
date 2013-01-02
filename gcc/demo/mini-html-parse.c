#include <stdio.h>

#include "../tools/chars.h"

static signed control (signed c);
static signed Content (signed c);
static signed control (signed c) 

{
	while (c != EOF) 
	{
		while ((c != '/') && (c != EOF)) 
		{
			if (c == '>') 
			{
				putc (c, stdout);
				c = getc (stdin);
				while ((c != '/') && (c != EOF)) 
				{
					while ((c != '<') && (c != EOF)) 
					{
						putc (c, stdout);
						c = getc (stdin);
					}
					putc ('<', stdout);
					c = getc (stdin);
					c = control (c);
				}
				putc ('/', stdout);
				c = getc (stdin);
				while ((c != '>') && (c != EOF)) 
				{
					putc (c, stdout);
					c = getc (stdin);
				}
				continue;
			}
			if (isspace (c)) 
			{
				do 
				{
					putc (c, stdout);
					c = getc (stdin);
				}
				while (isspace (c));
				continue;
			}
			if (isalpha (c)) 
			{
				do 
				{
					putc (c, stdout);
					c = getc (stdin);
				}
				while (isalnum (c));
				continue;
			}
			if (isquote (c)) 
			{
				signed o = c;
				putc (o, stdout);
				c = getc (stdin);
				while ((c != o) && (c != EOF)) 
				{
					putc (c, stdout);
					c = getc (stdin);
				}
				putc (o, stdout);
				c = getc (stdin);
				continue;
			}
			putc (c, stdout);
			c = getc (stdin);
		}
	}
	return (c);
}

int main (int argc, char const * argv []) 

{
	signed c = getc (stdin);
	c = content (c);
	return (0);
}

