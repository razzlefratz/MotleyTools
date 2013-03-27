/*====================================================================*
 *
 *   _math.h - math constants, structures, macros and functions;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef MATH_HEADER
#define MATH_HEADER

/*====================================================================*
 *   comparison, sign and truncation macros and functions;
 *--------------------------------------------------------------------*/

long _sgn (long x);
double _dsgn (double x);
int _iabs (int x);
long _labs (long x);
double _dabs (double x);

#ifdef X9D3W4

float fabs (float x);

#endif

double _ceil (double x);
double _floor (double x);

/*====================================================================*
 *   exponent, logrithm and power macros and functionsl
 *--------------------------------------------------------------------*/

double _e ();
double _exp (double x);
double frexp (double x, signed * exponent);
double ldexp (double x, signed exponent);
double _log10 (double x);
double _log (double x);
double _pow (double x, double y);
double _sqrt (double x);
long _ipow (long x, signed y);
double _dpow (double x, signed y);

/*====================================================================*
 *   angular computation macros and functions;
 *--------------------------------------------------------------------*/

#define PI (_atan(1)*(4))

#define DEGtoRAD (180.0/PI)
#define RADtoDEG (PI/180.0)

double _pi ();
double _cos (double x);
double _sin (double x);
double _tan (double x);
double _cosh (double x);
double _sinh (double x);
double _tanh (double x);
double _acos (double x);
double _asin (double x);
double _atan (double x);
double _atan2 (double y, double x);
double arccos (double x);
double arcsin (double x);
double arctan (double x);
double arctan2 (double y, double x);

/*====================================================================*
 *   modulo and blocking macros and function;
 *--------------------------------------------------------------------*/

double fmod (double x, double y);
double modf (double x, double * intpart);

/*====================================================================*
 *   quotient/remainder macros and functions;
 *--------------------------------------------------------------------*/

#ifndef DIV_T_HEADER
#define DIV_T_HEADER

typedef struct _div_t 

{
	int quot;
	int rem;
}

div_t;
typedef struct _ldiv_t 

{
	long quot;
	long rem;
}

ldiv_t;

#endif

div_t div (int x, int y);
ldiv_t ldiv (long int x, long int y);

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

