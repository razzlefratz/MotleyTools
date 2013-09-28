/*====================================================================*
 *
 *   obuffer.cpp - implementation of the obuffer class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oBUFFER_SOURCE
#define oBUFFER_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cerrno>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/obuffer.hpp"

/*====================================================================*
 *
 *   char const * offset() const
 *
 *   return the string used to indent buffer on output;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * obuffer::offset () const

{
	return (this->moffset);
}

/*====================================================================*
 *
 *   obuffer & offset (char const *offset);
 *
 *   define the string used to indent buffer on output;
 *
 *   this string often contains one tab or several spaces;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

obuffer & obuffer::offset (char const * offset)

{
	delete [] this->moffset;
	this->moffset = new char [std::strlen (offset) +  1];
	std::strcpy (this->moffset, offset);
	return (* this);
}

/*====================================================================*
 *
 *   char const * record () const
 *
 *   return the string used to terminate buffer on output;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * obuffer::record () const

{
	return (this->moffset);
}

/*====================================================================*
 *
 *   obuffer & record (char const *record);
 *
 *   define the string used to terminate buffer on output;
 *
 *   this string often contains one linefeed or semicolon;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

obuffer & obuffer::record (char const * record)

{
	delete [] this->mfinish;
	this->mfinish = new char [std::strlen (record) +  1];
	std::strcpy (this->mfinish, record);
	return (* this);
}

/*====================================================================*
 *
 *   obuffer & append (signed c);
 *
 *   append character c to buffer and return the character value;
 *   return but do not append EOF;
 *
 *   print a message and terminate the program on buffer overflow;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

obuffer & obuffer::append (signed c)

{
	if (c != EOF)
	{
		if (this->mlength >= this->mtotal)
		{
			char * buffer = this->mbuffer;
			while (this->mlength >= this->mtotal)
			{
				this->mtotal = this->mtotal +  this->mblock;
				this->mblock = this->mtotal - this->mblock;
			}
			this->mbuffer = new char [this->mtotal];
			std::memcpy (this->mbuffer, buffer, this->mlength);
			delete [] buffer;
		}
		this->mbuffer [this->mlength++] = (char) (c);
	}
	return (* this);
}

/*====================================================================*
 *
 *   obuffer & append (char const *string);
 *
 *   append a string to the text buffer and return the string address;
 *   return (char const *)(0) on failure;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

obuffer & obuffer::append (char const * string)

{
	if (string) for (char const * sp = string; * sp; ++ sp)
	{
		this->append (* sp);
	}
	return (* this);
}

/*====================================================================*
 *
 *   obuffer & level (signed level);
 *
 *   write text buffer to stdout preceded by the specified number of
 *   offset strings;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

obuffer & obuffer::level (signed level)

{
	while (level-- > 0)
	{
		std::cout.write (this->moffset, std::strlen (this->moffset));
	}
	this->flush ();
	return (* this);
}

/*====================================================================*
 *
 *   obuffer & space (signed space);
 *
 *   write text buffer to stdout followed by the specified number of
 *   record strings;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

obuffer & obuffer::space (signed space)

{
	this->flush ();
	while (space-- > 0)
	{
		std::cout.write (this->mfinish, std::strlen (this->mfinish));
	}
	return (* this);
}

/*====================================================================*
 *
 *   obuffer & flush ();
 *
 *   write text buffer to stdout;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

obuffer & obuffer::flush ()

{
	std::cout.write (this->mbuffer, this->mlength);
	this->mlength = 0;
	return (* this);
}

/*====================================================================*
 *
 *   obuffer & clear() :
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

obuffer & obuffer::clear ()

{
	this->mlength = 0;
	return (* this);
}

/*====================================================================*
 *
 *   obuffer()
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

obuffer::obuffer (size_t length)

{
	this->moffset = new char [2];
	this->moffset [0] = '\t';
	this->moffset [1] = '\0';
	this->mfinish = new char [2];
	this->mfinish [0] = '\n';
	this->mfinish [1] = '\0';
	this->mbuffer = new char [length];
	this->mlength = 0;
	this->mtotal = length;
	this->mblock = length;
	return;
}

/*====================================================================*
 *
 *   obuffer()
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

obuffer::obuffer ()

{
	this->moffset = new char [2];
	this->moffset [0] = '\t';
	this->moffset [1] = '\0';
	this->mfinish = new char [2];
	this->mfinish [0] = '\n';
	this->mfinish [1] = '\0';
	this->mbuffer = new char [512];
	this->mlength = 0;
	this->mtotal = 512;
	this->mblock = 512;
	return;
}

/*====================================================================*
 *
 *   ~obuffer()
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

obuffer::~ obuffer ()

{
	delete [] this->moffset;
	delete [] this->mfinish;
	delete [] this->mbuffer;
	return;
}

/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif



