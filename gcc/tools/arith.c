/*====================================================================*
 *
 *   arith.c - integer arithmetic expression scanner and evaluator;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

#include "../tools/number.h"
#include "../tools/symbol.h"
#include "../tools/chars.h"

/*====================================================================*
 *
 *   int _numb (void * bp, int get (void * bp), int unget (int c, void *bp));
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

static int _numb (void * bp, int get (void * bp), int unget (int c, void * bp)) 

{
	int c = get (bp);
	int n = 0;
	while (isdigit (c)) 
	{
		n *= 10;
		n += (c - '0');
		c = get (bp);
	}
	unget (c, bp);
	return (n);
}


/*====================================================================*
 *
 *   int _fact (void * bp)
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

static int _fact (void * bp, int get (void * bp), int unget (int c, void * bp)) 

{
	signed c;
	int n = 1;
	while ((c = get (bp)) != EOF) 
	{
		if (isblank (c)) continue;
		else if (isdigit (c)) 
		{
			unget (c, bp);
			n *= _numb (bp, get, unget);
		}
		else if (c == '(') 
		{
			n *= _numb (bp, get, unget);
			if ((c = get (bp)) != ')') unget (c, bp);
		}
		else 
		{
			unget (c, bp);
			break;
		}
	}
	return (n);
}


/*====================================================================*
 *
 *   int _term (void * bp, int get (void * bp), int unget (int c, void * bp))
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

static int _term (void * bp, int get (void * bp), int unget (int c, void * bp)) 

{
	extern signed c;
	int n = _fact (bp, get, unget);
	while ((c = get (bp)) != EOF) 
	{
		if (isblank (c)) continue;
		else if (c == '*') n *= _fact (bp, get, unget);
		else if (c == '/') n /= _fact (bp, get, unget);
		else if (c == '%') n %= _fact (bp, get, unget);
		else 
		{
			unget (c, bp);
			break;
		}
	}
	return (n);
}


/*====================================================================*
 *
 *   int value (void * bp, int get(void * bp), int unget(int c, void * bp))
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

int value (void * bp, int get (void * bp), int unget (int c, void * bp)) 

{
	extern signed c;
	int n = _term (bp, get, unget);
	while ((c = get (bp)) != EOF) 
	{
		if (isblank (c)) continue;
		else if (c == '+') n += _term (bp, get, unget);
		else if (c == '-') n -= _term (bp, get, unget);
		else 
		{
			unget (c, bp);
			break;
		}
	}
	return (n);
}

