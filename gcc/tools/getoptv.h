/*====================================================================*
 *
 *   getoptv.h - getoptv related definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 2005 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GETOPTV_HEADER
#define GETOPTV_HEADER

/*====================================================================*
 *   constant definitions;
 *--------------------------------------------------------------------*/

#define GETOPTV_VERSION 1
#define GETOPTV_SUMMARY 1

#define GETOPTV_C_OPTION  ('-')
#define GETOPTV_C_IGNORE  ('!')
#define GETOPTV_C_OPERAND (':') 
#define GETOPTV_C_ILLEGAL ('?') 
#define GETOPTV_C_VERSION ('!') 
#define GETOPTV_C_SUMMARY ('?') 

/*====================================================================*
 *   variable declarations;
 *--------------------------------------------------------------------*/

extern char * optarg;
extern signed optopt;
extern signed optind;
extern signed opterr;
extern signed optmin;

/*====================================================================*
 *   function declarations;
 *--------------------------------------------------------------------*/

signed getoptv (int argc, char const * argv [], char const * optv []);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif



