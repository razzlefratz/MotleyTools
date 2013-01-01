/*====================================================================*
 *
 *   value.c - convert arithmetic expression to signed integer;  
 *
 *   symbol.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/symbol.h"

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

static signed c;

/*====================================================================*
 *
 *   signed _number (void * op, signed get (void * op), signed unget (signed c, void * op));
 *
 *   <integer> :== <space> <integer>
 *   <integer> :== <integer> <digit>
 *   <integer> :== <digit>
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static signed _number (void * op, signed get (void * op), signed unget (signed c, void * op)) 

{
	signed n = 0;
	while (isdigit (c)) 
	{
		n *= 10;
		n += (c - '0');
		c = get (op);
	}
	printf ("number=%d\n", n);
	return (n);
}


/*====================================================================*
 *
 *   signed _factor (void * op)
 *
 *   <factor> :== <number>
 *   <factor> :== ( <expression> )
 *   <factor> :== <factor>( <expression> )
 *   <factor> :== <factor> <number>
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static signed _factor (void * op, signed get (void * op), signed unget (signed c, void * op)) 

{
	signed n = 1;
	while (c != EOF) 
	{
		if (isblank (c)) 
		{
			c = get (op);
			continue;
		}
		if (isdigit (c)) 
		{
			n *= _number (op, get, unget);
			continue;
		}
		if (c == '(') 
		{
			n *= value (op, get, unget);
			if (c == ')') 
			{
				c = get (op);
			}
			continue;
		}
		break;
	}
	printf ("factor=%d\n", n);
	return (n);
}


/*====================================================================*
 *
 *   signed _term (void * op, signed get (void * op), signed unget (signed c, void * op))
 *
 *   <term> :== <factor>
 *   <term> :== <term> * <factor>
 *   <term> :== <term> / <factor>
 *   <term> :== <term> % <factor>
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static signed _term (void * op, signed get (void * op), signed unget (signed c, void * op)) 

{
	signed n = _factor (op, get, unget);
	while (c != EOF) 
	{
		if (isblank (c)) 
		{
			c = get (op);
			continue;
		}
		if (c == '*') 
		{
			c = get (op);
			n *= _factor (op, get, unget);
			continue;
		}
		if (c == '/') 
		{
			c = get (op);
			n /= _factor (op, get, unget);
			continue;
		}
		if (c == '%') 
		{
			c = get (op);
			n %= _factor (op, get, unget);
			continue;
		}
		break;
	}
	printf ("term=%d\n", n);
	return (n);
}


/*====================================================================*
 *
 *   signed value (void * op, signed get (void * op), signed unget (signed c, void * op))
 *
 *   symbol.h
 *
 *   <arith> :== <term>
 *   <arith> :== <arith> + <term>
 *   <arith> :== <arith> - <term>
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed value (void * op, signed get (void * op), signed unget (signed c, void * op)) 

{
	c = get (op);
	signed n = _term (op, get, unget);
	while (c != EOF) 
	{
		if (isblank (c)) 
		{
			c = get (op);
			continue;
		}
		if (c == '+') 
		{
			c = get (op);
			n += _term (op, get, unget);
			continue;
		}
		if (c == '-') 
		{
			c = get (op);
			n -= _term (op, get, unget);
			continue;
		}
		break;
	}
	return (n);
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#if 0

#include <stdio.h>

int main (int argc, char const * argv []) 

{
	printf ("%d\n", value (stdin, getc, ungetc));
	return (0);
}


#endif

