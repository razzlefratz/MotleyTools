/*====================================================================*
 *
 *   getopt.h - getopt related definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  compiled for debian gnu/linux environment using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef GETOPT_HEADER
#define GETOPT_HEADER

#if defined(__linux__)
#define _GETOPT_H
#elif defined(__APPLE__)
#define _GETOPT_H_
#endif

/*====================================================================*
 *   constant definitions;
 *--------------------------------------------------------------------*/

#define GETOPT_VERSION 1
#define GETOPT_SUMMARY 1

#define GETOPT_C_OPTION  ('-')
#define GETOPT_C_OPERAND (':') 
#define GETOPT_C_ILLEGAL ('?') 
#define GETOPT_C_VERSION ('!') 
#define GETOPT_C_SUMMARY ('?') 

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

signed getopt(int argc, char * argv[], char const * options);

/*====================================================================*
 *   end definitions;
 *--------------------------------------------------------------------*/

#endif



