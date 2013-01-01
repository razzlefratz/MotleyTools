/*====================================================================*
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>

float fvalue (void *bp, int get (void *bp), int unget (int c, void *bp));

/*====================================================================*
 *
 *   float _numb(void *fp, int get(void *fp), int unget(int c, void *fp));
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

static float _numb (void *bp, int get (void *bp), int unget (int c, void *bp)) 

{
	float n = 0.0;
	float p = 1.0;
	int c = get (bp);
	while (isdigit (c)) 
	{
		n *= 10.0;
		n += (c)-('0');
		c = get (bp);
	}
	if (c == '.') 
	{
		c = get (bp);
	}
	while (isdigit (c)) 
	{
		p *= 10.0;
		n *= 10.0;
		n += (c)-('0');
		c = get (bp);
	}
	unget (c, bp);
	return (n/p);
}


/*====================================================================*
 *
 *   float _fact(void *bp)
 *
 *   <factor> :== <space> <factor>
 *   <factor> :== ( <expression> )
 *   <factor> :== <number>
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static float _fact (void *bp, int get (void *bp), int unget (int c, void *bp)) 

{
	signed c;
	float n = 1.0;
	while ((c = get (bp)) != EOF) 
	{
		if (isspace (c)) continue;
		else if (isdigit (c)) 
		{
			unget (c, bp);
			n *= _numb (bp, get, unget);
		}
		else if (c == '(') 
		{
			n *= fvalue (bp, get, unget);
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
 *   float _term(void *bp, int get(void *bp), int unget(int c, void *bp))
 *
 *   <term> :== <factor>
 *   <term> :== <term> * <factor>
 *   <term> :== <term> / <factor>
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static float _term (void *bp, int get (void *bp), int unget (int c, void *bp)) 

{
	signed c;
	float n = _fact (bp, get, unget);
	while ((c = get (bp)) != EOF) 
	{
		if (isspace (c)) continue;
		else if (c == '*') n *= _fact (bp, get, unget);
		else if (c == '/') n /= _fact (bp, get, unget);
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
 *   float fvalue(void *bp, int get(void *bp), int unget(int c, void *bp))
 *
 *   <value> :== <term>
 *   <value> :== <value> + <term>
 *   <value> :== <value> - <term>
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

float fvalue (void *bp, int get (void *bp), int unget (int c, void *bp)) 

{
	signed c;
	float n = _term (bp, get, unget);
	while ((c = get (bp)) != EOF) 
	{
		if (isspace (c)) continue;
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

