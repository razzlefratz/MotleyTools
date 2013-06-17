/*====================================================================*
 *
 *   oformat.cpp - implementation of the oformat class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *
 *--------------------------------------------------------------------*/

#ifndef oFORMAT_SOURCE
#define oFORMAT_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>
#include <cstring>
#include <cstdlib>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oformat.hpp"

/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/

#define BUFFER_MAX 96 
#define SP ' '

/*====================================================================*
 *
 *   unsigned oformat::column() const;
 *
 *   return the current column position;
 *
 *--------------------------------------------------------------------*/

unsigned oformat::column () const 

{
	return (this->mcolumn);
}


/*====================================================================*
 *
 *   unsigned int oformat::margin(unsigned margin);
 *
 *  return or define the text margin; the text margin may be any positive
 *  value;
 *
 *--------------------------------------------------------------------*/

unsigned oformat::margin () const 

{
	return (this->mmargin);
}


oformat & oformat::margin (unsigned margin) 

{
	this->mmargin = margin;
	return (* this);
}


/*====================================================================*
 *
 *   unsigned oformat::length(unsigned length);
 *
 *   define the text length; the text length cannot exceed the text record;
 *
 *--------------------------------------------------------------------*/

unsigned oformat::length () const 

{
	return (this->mlength);
}


oformat & oformat::length (unsigned column) 

{
	this->mlength = column;
	if (this->mlength > this->mrecord) 
	{
		this->mlength = this->mrecord;
	}
	if (this->mlength < this->mindent) 
	{
		this->mindent = this->mlength;
	}
	return (* this);
}


/*====================================================================*
 *
 *   unsigned int oformat::indent(unsigned column);
 *
 *   define the text indent; the text indent cannot exceed the text length;
 *
 *--------------------------------------------------------------------*/

unsigned oformat::indent () const 

{
	return (this->mindent);
}


oformat & oformat::indent (unsigned column) 

{
	this->mindent = column;
	if (this->mindent > this->mlength) 
	{
		this->mindent = this->mlength;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oformat & oformat::offset(unsigned column);
 *
 *   define the text offset; the text offset cannot exceed the text length;
 *   the offset reset to the text indent after the buffer is flushed; 
 *
 *--------------------------------------------------------------------*/

unsigned oformat::offset () const 

{
	return (this->moffset);
}


oformat & oformat::offset (unsigned column) 

{
	this->moffset = column;
	if (this->moffset > this->mlength) 
	{
		this->moffset = this->mlength;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oformat & oformat::table(unsigned offset);
 *
 *   this function advances the tempory indent to the next column that is
 *   an even multiple of the specified count; 
 *
 *--------------------------------------------------------------------*/

oformat & oformat::table (unsigned count) 

{
	for (this->moffset++; this->moffset % count; this->moffset++);
	return (* this);
}


oformat & oformat::shift (unsigned count) 

{
	this->moffset = this->moffset + count;
	if (this->moffset > this->mlength) 
	{
		this->moffset = this->mlength;
	}
	return (* this);
}


/*====================================================================*
 *
 *   oformat & space(unsigned count);
 *
 *   remove trailing spaces then append the specified number of spaces; 
 *
 *--------------------------------------------------------------------*/

oformat & oformat::space (unsigned count) 

{
	while ((this->mcolumn > this->moffset) && (this->mbuffer [this->mcolumn - 1] == SP)) 
	{
		this->mcolumn--;
	}
	if (this->mcolumn > this->moffset) 
	{
		while ((count-- > 0) & (this->mcolumn < this->mlength)) 
		{
			this->mbuffer [this->mcolumn++] = SP;
		}
	}
	return (* this);
}


/*====================================================================*
 *
 *   void print(char *string);
 *
 *   this function appends a string to the end of the output buffer;
 *
 *--------------------------------------------------------------------*/

oformat & oformat::print (char const * string) 

{
	this->align ();
	if (this->mcolumn + std::strlen (string) >= this->mlength) 
	{
		this->space (0);
		this->flush (0);
		this->align ();
	}
	while (* string) 
	{
		if (* string == '\n') 
		{
			this->space (0);
			this->flush (0);
			this->align ();
			string++;
		}
		else if (this->mcolumn < this->mlength) 
		{
			this->mbuffer [this->mcolumn++] = * string++;
		}
		else 
		{
			this->space (0);
			this->flush (0);
			this->align ();
		}
	}
	return (* this);
}


/*====================================================================*
 *
 *   void flush(unsigned space);
 *
 *   flush() prints the contents of the output buffer and a terminating
 *   newline unless the buffer is empty or a minimum output line count has
 *   been specified.
 *
 *--------------------------------------------------------------------*/

oformat & oformat::flush (unsigned space) 

{
	if (this->mcolumn > 0) 
	{
		this->mbuffer [this->mcolumn++] = '\n';
		this->mbuffer [this->mcolumn++] = '\0';
		for (this->mcolumn = this->mmargin; this->mcolumn > 0; this->mcolumn--) 
		{
			fputc ('$', stdout);
		}
		fputs (this->mbuffer, stdout);
		this->moffset = this->mindent;
		this->mcolumn = 0;
	}
	while (space-- > 0) 
	{
		fputc ('\n', stdout);
	}
	return (* this);
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

oformat & oformat::align () 

{
	while (this->mcolumn < this->moffset) 
	{
		this->mbuffer [this->mcolumn++] = SP;
	}
	return (* this);
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

oformat & oformat::status () 

{
	std::cout << "margin=(" << this->mmargin << ")" << std::endl;
	std::cout << "indent=(" << this->mindent << ")" << std::endl;
	std::cout << "offset=(" << this->moffset << ")" << std::endl;
	std::cout << "column=(" << this->mcolumn << ")" << std::endl;
	std::cout << "length=(" << this->mlength << ")" << std::endl;
	std::cout << "record=(" << this->mrecord << ")" << std::endl;
	return (* this);
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

oformat::oformat () 

{
	this->mbuffer = new char [BUFFER_MAX];
	this->mmargin = 0;
	this->mindent = 0;
	this->moffset = 0;
	this->mcolumn = 0;
	this->mlength = BUFFER_MAX;
	this->mrecord = BUFFER_MAX;
	return;
}


oformat::~oformat () 

{
	this->flush (0);
	delete [] this->mbuffer;
	return;
}


/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif

