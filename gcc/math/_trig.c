/*====================================================================*
 *
 *   _trig.c - compile math library trig functions as one module;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef _TRIG_SOURCE
#define _TRIG_SOURCE

#include "../math/_math.h"

#ifdef STAND_ALONE
#include "../math/_e.c"
#include "../math/_exp.c"
#endif

double _pi () 

{
	return (_atan (1) * 4);
}

double torad (double deg) 

{
	return (_atan (1) * deg / 45);
}

double todeg (double rad) 

{
	return (45 * rad / _atan (1));
}


#ifdef STAND_ALONE
#include "../math/_cos.c"
#include "../math/_sin.c"
#endif

double tan (double x) 

{
	return (_sin (x) / _cos (x));
}

double _sec (double x) 

{
	return (1 / _cos (x));
}

double _cosec (double x) 

{
	return (1 / _sin (x));
}

double _cotan (double x) 

{
	return (1 / _tan (x));
}


#ifdef STAND_ALONE
#include "../math/_cosh.c"
#include "../math/_sinh.c"
#endif

double _tanh (double x) 

{
	return (_sinh (x) / _cosh (x));
}

double _sech (double x) 

{
	return (1 / _cosh (x));
}

double _cosech (double x) 

{
	return (1 / _sinh (x));
}

double _cotanh (double x) 

{
	return (1 / _tanh (x));
}

double _arcsin (double x) 

{
	if (x == 1.0) 
	{
		return (_atan (1) * 2);
	}
	else if (x == -1.0) 
	{
		return (_atan (1) * -2);
	}
	else return (_atan (x / _sqrt (-x * x + 1)));
}

double _arccos (double x) 

{
	if (x == 1.0) 
	{
		return (0);
	}
	else if (x == -1.0) 
	{
		return (_atan (1) * -4);
	}
	else return (_atan (x / _sqrt (-x * x + 1)) + _atan (1) * 2);
}

double _arctan (double x) 

{
	return (_atan (x));
}

double _arccosh (double x) 

{
	return (_log (x + _sqrt (x * x - 1)));
}

double _arcsinh (double x) 

{
	return (_log (x + _sqrt (x * x + 1)));
}

double _arctanh (double x) 

{
	return (_log ((1 + x) / (1 - x)) / 2);
}

double _arcsech (double x) 

{
	return (_log ((_sqrt (-x * x + 1) + 1) / x));
}

double _arccosech (double x) 

{
	return (_log ((_dsgn (x) * _sqrt (x * x + 1) + 1) / x));
}

double _arccotanh (double x) 

{
	return (_atan (x) + _atan (1) * 2);
}


#endif

