/*====================================================================*
 *
 *   oerror.cpp - implementation of the oerror class.
 *
 *   this class implements the useful GNU error() and error_at_line()
 *   functions with some additions;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oERROR_SOURCE
#define oERROR_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <cerrno>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oerror.hpp"
#include "../classes/types.h"

/*====================================================================*
 *   program variables; 
 *--------------------------------------------------------------------*/

extern char const * program_name;

/*====================================================================*
 *
 *   void oerror::print (char const *format, ...);
 *
 *   print error messages using a variable argument list; prefix all
 *   messages with the program_name string; suffix all messages with 
 *   the text returned by strerror(error);
 *
 *--------------------------------------------------------------------*/

void oerror::print (char const *format, ...) 

{
	if ((program_name) && (*program_name)) 
	{
		std::cerr << program_name << ": ";
	}
	if ((format) && (*format)) 
	{
		va_list argp;
		va_start (argp, format);
		std::vfprintf (stderr, format, argp);
		va_end (argp);
	}
	std::cerr << std::endl;
	return;
}


/*====================================================================*
 *
 *   void oerror::error (char const * format, ...);
 *
 *   print an error message using variable argument list; prefix all
 *   messages with program_name; append strerror() message text when
 *   errno is non-zero;
 *
 *--------------------------------------------------------------------*/

void oerror::error (char const * format, ...) 

{
	if ((program_name) && (*program_name)) 
	{
		std::cerr << program_name << ": ";
	}
	if (errno) 
	{
		std::cerr << std::strerror (errno) << ": ";
		errno = 0;
	}
	if ((format) && (*format)) 
	{
		va_list argp;
		va_start (argp, format);
		std::vfprintf (stderr, format, argp);
		va_end (argp);
	}
	std::cerr << std::endl;
	return;
}


/*====================================================================*
 *
 *   void error (int code, errno_t error, char const * format, ...);
 *
 *   print an error message using variable argument list; prefix all
 *   messages with program_name; append strerror() message text when
 *   number is not non-zero; exit with status if status is non-zero;
 *
 *   included for compatibility with the GNU C library;
 *
 *--------------------------------------------------------------------*/

void oerror::error (int status, errno_t number, char const * format, ...) 

{
	if ((program_name) && (* program_name)) 
	{
		std::cerr << program_name << ": ";
	}
	if (number) 
	{
		std::cerr << std::strerror (number) << ": ";
		errno = 0;
	}
	if ((format) && (*format)) 
	{
		va_list arglist;
		va_start (arglist, format);
		std::vfprintf (stderr, format, arglist);
		va_end (arglist);
	}
	std::cerr << std::endl;
	if (status) 
	{
		std::exit (status);
	}
	return;
}


/*====================================================================*
 *
 *   void error (int status, char const * string, char const * format, ...);
 *
 *   print an error message using variable argument list; prefix all
 *   messages with program_name; append strerror() message text when
 *   number is not non-zero; exit with status if status is non-zero;
 *
 *   included for compatibility with the GNU C library;
 *
 *--------------------------------------------------------------------*/

void oerror::error (int status, char const * string, char const * format, ...) 

{
	if ((program_name) && (* program_name)) 
	{
		std::cerr << program_name << ": ";
	}
	if ((string) && (* string)) 
	{
		std::cerr << string << ": ";
		errno = 0;
	}
	if ((format) && (* format)) 
	{
		va_list arglist;
		va_start (arglist, format);
		std::vfprintf (stderr, format, arglist);
		va_end (arglist);
	}
	std::cerr << std::endl;
	if (status) 
	{
		std::exit (status);
	}
	return;
}


/*====================================================================*
 *
 *   void error_at_line (int status, errno_t number, char const * file, unsigned line, char const * format, ...);
 *
 *   print error messages using a variable argument list; prefix all
 *   messages with the program_name string; suffix messages with the
 *   text returned by strerror(error) if error is not 0; exit with
 *   code if code is not 0; include filename and lineno; 
 *
 *   included for compatibility with the GNU C library;
 *
 *--------------------------------------------------------------------*/

void oerror::error_at_line (int status, errno_t number, char const * file, unsigned line, char const * format, ...) 

{
	if ((program_name) && (* program_name)) 
	{
		std::cerr << program_name << ": ";
	}
	if ((file) && (* file)) 
	{
		std::cerr << file << " (" << line << "): ";
	}
	if (number) 
	{
		std::cerr << std::strerror (number) << ": ";
	}
	if ((format) && (* format)) 
	{
		va_list arglist;
		va_start (arglist, format);
		std::vfprintf (stderr, format, arglist);
		va_end (arglist);
	}
	std::cerr << std::endl;
	if (status) 
	{
		std::exit (status);
	}
	return;
}


/*====================================================================*
 *   
 *   oerror ();
 *   
 *   
 *--------------------------------------------------------------------*/

oerror::oerror () 

{
	extern char const * program_name;
	if (!program_name) 
	{

#if defined (__linux__)

		program_name = ::getlogin ();

#else

		program_name = "program";

#endif

	}
	errno = 0;
	return;
}


/*====================================================================*
 *   
 *   ~oerror ();
 *   
 *   
 *--------------------------------------------------------------------*/

oerror::~oerror () 

{
	return;
}


/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

