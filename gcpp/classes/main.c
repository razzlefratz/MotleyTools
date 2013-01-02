#include <stdio.h>
#include <string.h>
#include <ctype.h>

static signed keep (signed c) 

{
	if (c != EOF) 
	{
		putc (c, stdout);
		c = getc (stdin);
	}
	return (c);
}

int main (int argc, char const * argv []) 

{
	char buffer [512];
	signed c = getc (stdin);
	while (c != EOF) 
	{
		if (isalpha (c)) 
		{
			char * cp = buffer;
			do { * cp++ = c; c = keep (c); } while (isalpha (c) || (c == '_'));
			*cp = (char)(0);
			if (!strcmp (buffer, "echo")) 
			{
				if (c == ' ') 
				{
					c = keep (c);
				}
				if (c == '(') 
				{
					c = keep (c);
				}
				if (c == '\'') 
				{
					signed o = '\"';
					signed e = keep (o);
					while ((e != c) && (e != EOF)) 
					{
						if (e == o)
						{
							e = c;
						}
						if (e == '\\')
						{
							putc (e, stderr);
							e = keep (e);
						}
						putc (e, stderr);
						e = keep (e);
					}
					putc ('\n', stderr);
					c = keep (o);
				}
			}
		}
		else if ((c == '\'') || (c == '\"')) 
		{
			signed e = keep (c);
			while ((e != c) && (e != EOF)) 
			{
				if (e == '\\')
				{
					e = keep (e);
				}
				e = keep (e);
			}
			c = keep (e);
		}
		else 
		{
			c = keep (c);
		}
	}
	return (0);
}

