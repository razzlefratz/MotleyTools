/*====================================================================*
 *
 *   getoptv.h - getopt related definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GETOPTV_HEADER
#define GETOPTV_HEADER

/*====================================================================*
 *   constant definitions;
 *--------------------------------------------------------------------*/

#define GETOPTV_PROGRAM 1

// #define GETOPTV_NETWORK 1

#define GETOPTV_VERSION 1
#define GETOPTV_SUMMARY 1

#define GETOPT_C_OPTION  ('-')
#define GETOPT_C_OPERAND (':') 
#define GETOPT_C_ILLEGAL ('?') 
#define GETOPT_C_VERSION ('!') 
#define GETOPT_C_SUMMARY ('?') 

/*====================================================================*
 *   variable declarations;
 *--------------------------------------------------------------------*/

extern char const *optapp;
extern char const *optarg;
extern signed optopt;
extern signed optind;
extern signed opterr;

/*====================================================================*
 *   function declarations;
 *--------------------------------------------------------------------*/

signed getoptv (int argc, char const *argv [], char const *optv []);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif

