/*====================================================================*
 *
 *   okeywords.cpp - okeywords class implementation;
 *
 *   implement a generic keyword lookup table;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oKEYWORDS_SOURCE
#define oKEYWORDS_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>
#include <cstdlib>
#include <cstring>

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#include "../classes/okeywords.hpp"
#include "../classes/types.h"

/*====================================================================*
 *   class variables;    
 *--------------------------------------------------------------------*/

char const * okeywords::table [] = 

{
	(char const *) (0)
};

const unsigned okeywords::words = SIZEOF (okeywords::table) - 1;

/*====================================================================*
 *
 *   size_t count () const;
 *
 *   return the keyword count;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

size_t okeywords::count () const 

{
	return (this->mcount);
}

/*====================================================================*
 *
 *   char const keywords (size_t index) const;
 *
 *   return a keyword string by keyword index;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

char const * okeywords::keywords (size_t index) const 

{
	return (index < this->mcount? this->mtable [index]: this->mtable [this->mcount]);
}

/*====================================================================*
 *
 *   bool defined (char const *string) const;
 *
 *   return true if a keyword is present in the keyword table;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool okeywords::defined (char const * string) const 

{
	return (this->indexof (string) < this->mcount);
}

/*====================================================================*
 *
 *   unsigned indexof (char const *string) const;
 *
 *   return the keyword index, if present, or the keyword count, if
 *   missing; use a binary table search;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

size_t okeywords::indexof (char const * string) const 

{
	size_t lower = 0;
	size_t upper = this->mcount;
	while (lower < upper) 
	{
		size_t index = (lower + upper) >> 1;
		signed order = std::strcmp (string, this->mtable [index]);
		if (order < 0) 
		{
			upper = index - 0;
			continue;
		}
		if (order > 0) 
		{
			lower = index + 1;
			continue;
		}
		return (index);
	}
	return (this->mcount);
}

/*====================================================================*
 *
 *   size_t longest () const
 *
 *   return the length of the longest stored keyword;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

size_t okeywords::longest () const 

{
	size_t length = 0;
	for (size_t count = 0; count < this->mcount; count++) 
	{
		size_t width = std::strlen (this->mtable [count]);
		if (width > length) 
		{
			length = width;
		}
	}
	return (length);
}

/*====================================================================*
 *
 *   okeywords & enumerate (); 
 *
 *   print a C Language source code table definition on stdout;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

okeywords & okeywords::enumerate () 

{
	unsigned index;
	std::cout << "/*=*" << std::endl;
	std::cout << " *   " << this->mtitle << " table definitions;" << std::endl;
	std::cout << " *-*/" << std::endl;
	std::cout << std::endl;
	for (index = 0; index < this->mcount; index++) 
	{
		std::cout << "#define " << this->mtitle << "_o_" << this->mtable [index] << " " << index << std::endl;
	}
	std::cout << "#define " << this->mtitle << " " << this->mcount << std::endl;
	std::cout << std::endl;
	std::cout << "/*=*\n *   " << this->mtitle << " table declaration;\n *-*/" << std::endl;
	std::cout << std::endl;
	std::cout << "\tconst size_t " << this->mtitle << "::count = " << this->mtitle << std::endl;
	std::cout << "\tchar const * " << this->mtitle << "::table [" << this->mtitle << "+1] = " << std::endl;
	std::cout << "\t{" << std::endl;
	for (index = 0; index < this->mcount; index++) 
	{
		std::cout << "\t\t\"" << this->mtable [index] << "\"," << std::endl;
	}
	std::cout << "\t\t(char const *)(0)" << std::cout;
	std::cout << "\t};" << std::endl;
	std::cout << std::endl;
	std::cout << "/*=*" << std::endl;
	std::cout << " *   " << this->mtitle << " table enumeration;" << std::endl;
	std::cout << " *-*/" << std::endl;
	std::cout << std::endl;
	std::cout << "\toffset = object->indexof(this->mtitle);" << std::endl;
	std::cout << std::endl;
	std::cout << "\tswitch(offset)" << std::endl;
	std::cout << "\t{" << std::endl;
	for (index = 0; index < this->mcount; index++) 
	{
		std::cout << "\t\tcase " << this->mtitle << "_o_" << this->mtable [index] << ":" << std::endl;
		std::cout << "\t\t\tbreak;" << std::endl;
	}
	std::cout << "\t\tdefault:" << std::endl;
	std::cout << "\t\t\tbreak;" << std::endl;
	std::cout << "\t}" << std::endl;
	std::cout << std::endl;
	return (* this);
}

/*====================================================================*
 *
 *   okeywords & enumerate (char const *prefix, char const *suffix);
 *
 *   print keywords, with prefix and suffix strings, on stdout; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

okeywords & okeywords::enumerate (char const * prefix, char const * suffix) 

{
	unsigned index = 0;
	while (index < this->mcount) 
	{
		std::cout << prefix << this->mtable [index++] << suffix;
	}
	return (* this);
}

/*====================================================================*
 *
 *   okeywords & okeywords::enumerate (unsigned screenwidth);
 *
 *   print keywords on stdout as a series of vertical columns where
 *   words are listed vertically in alphabetical order;
 *
 *   compute column width from vector string lengths; compute number 
 *   of columns from screen and column widths;  
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

okeywords & okeywords::enumerate (size_t columns) 

{
	size_t width = 0;
	size_t count = 0;
	size_t block = 0;
	while (count < this->mcount) 
	{
		block = std::strlen (this->mtable [count++]);
		if (block > width) 
		{
			width = block;
		}
	}
	if (width++ < columns) 
	{
		count = columns / width;
		block = (this->mcount + count - 1) / count;
		width = columns / count;
		std::cout.put ('\n');
		for (size_t row = 0; row < block; row++) 
		{
			for (count = row; count < this->mcount; count += block) 
			{
				char const * string = this->mtable [count];
				while ((string - this->mtable [count]) < (signed)(width)) 
				{
					if (* string) 
					{
						std::cout.put (* string++);
						continue;
					}
					break;
				}
				while ((string - this->mtable [count]) < (signed)(width)) 
				{
					std::cout.put (' ');
					string++;
				}
			}
			std::cout.put ('\n');
		}
		std::cout.put ('\n');
	}
	return (* this);
}

/*====================================================================*
 *
 *   okeywords & mcheck (); 
 *
 *   count keywords and confirm they are in order; report any error 
 *   and exit program on failure; this ensures that a binary search 
 *   will not fail to find words;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

okeywords & okeywords::mcheck () 

{
	size_t count = 0;
	while (this->mtable [count]) 
	{
		count++;
	}
	if (count != this->mcount) 
	{
		std::cerr << this->mtitle << ": Have " << count << " keywords but expected " << this->mcount << "." << std::endl;
		std::exit (1);
	}
	for (count = 1; count < this->mcount; count++) 
	{
		if (std::strcmp (this->mtable [count-1], this->mtable [count]) > 0) 
		{
			std::cerr << this->mtitle << ": Keyword \"" << this->mtable [count-1] << "\" is out of order." << std::endl;
			std::exit (1);
		}
	}
	return (* this);
}

/*====================================================================*
 *
 *   okeywords ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

okeywords::okeywords () 

{
	this->mtitle = "keywords";
	this->mcount = okeywords::words;
	this->mtable = okeywords::table;
	return;
}

/*====================================================================*
 *
 *   okeywords::~okeywords ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

okeywords::~okeywords () 

{
	return;
}

/*====================================================================*
 *   end implementation;
 *--------------------------------------------------------------------*/

#endif

