/*====================================================================*
 *
 *   calc.h - math constants, structures, macros and functions;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sat 11 oct 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *   environment is gnu gcc compiler under devian linux;
 *
 *--------------------------------------------------------------------*/

#ifndef CALC_HEADER
#define CALC_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stddef.h>
#include <stdint.h>

/*====================================================================*
 *   comparison, sign and truncation macros and functions;
 *--------------------------------------------------------------------*/

#define _max(x,y) ((x)>(y)?(x):(y))
#define _min(x,y) ((x)<(y)?(x):(y))
#define _cmp(x,y) ((x)>(y)?(int)(1):(x)<(y)?(int)(-1):(int)(0))

#define _sgn(x) ((x)<(0)?(-1):(1))
#define _abs(x) ((x)<(0)?(-x):(x))

/*====================================================================*
 *   exponent, logrithm and power macros and functionsl
 *--------------------------------------------------------------------*/

double log (double x);
double logn (double value, unsigned base);

#define _logn(value,base) (log(value)/log(base))
#define _log10(value) logn(value,10)

long ipow (int x, int y);
double dpow (double x, int y);

/*====================================================================*
 *   angular computation macros and functions;
 *--------------------------------------------------------------------*/

#define _torad(x) ((float)(x)*((PI)/(180.0)))
#define _todeg(x) ((float)(x)*((180.0)/(PI)))

/*====================================================================*
 *   modulo and blocking macros and function;
 *--------------------------------------------------------------------*/

double fmod (double x, double y);
unsigned pmod (signed domain, signed range);
unsigned qmod (signed domain, signed range);

#define _fmod(n,b) (double)((n)-(long)((n)/(b))*(b)))
#define _pmod(n,b) ((((n)%=(b))<0)?(n)+(b):(n))
#define _qmod(n,b) ((((n)%=(b))>0)?(n):(n)+(b))

int nblock (int count, int block);

#define _nblock(n,m) (((n)>0)&&((m)>0))?((n)+(m)-1)/(m):0)

/*====================================================================*
 *   common divisor/multiple macros and functions;
 *--------------------------------------------------------------------*/

long gcd (long n, long m);
long lcm (long n, long m);

#define _lcm(n,y) ((x)*(y))/gcd((x),(y)));

void _srand (uint32_t seed);
uint32_t _rand ();

/*====================================================================*
 *   full/partial factoral macros and functions;
 *--------------------------------------------------------------------*/

long ifact (int x);
long pfact (int x, int y);
void smooth (double sample [], int size, int span);
double range (double sample [], size_t size, double *minimum, double *maximum, double *average, double *sigma);

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

