/*====================================================================*
 *
 *   oblock.cpp - C Language blocker;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef OCBLOCK_SOURCE
#define OCBLOCK_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstring>
#include <cstdio>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/stdafx.hpp"
#include "../classes/ocblock.hpp"
#include "../classes/oascii.hpp"

/*====================================================================*
 *
 *   ocblock & level (signed level);
 *
 *   change level counter value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

ocblock & ocblock::level (signed level) 

{
	this->mlevel = level;
	return (*this);
}


/*====================================================================*
 *
 *   signed level () const;
 *
 *   return level counter value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

signed ocblock::level ()const 

{
	return (this->mlevel);
}


/*====================================================================*
 *
 *   signed ocblock::preamble (signed c);
 *
 *   conditionally print an empty preamble comment block; return
 *   character c unchanged;
 *   
 *.  Motley Tools by Charles Maier;
 *:  Copyright (c) 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

signed ocblock::preamble (signed c)
{
	if (!this->mlevel)
	{
		while (c != EOF)
		{
			if (c == '/')
			{
				c = ocblock::comment (c);
				continue;
			}
			if (c == ';')
			{
				c = ocblock::keep (c);
				continue;
			} 
			if (oascii::isspace (c))
			{
				c = ocblock::keep (c);
				continue;
			} 
			std::cout << std::endl << std::endl;
			std::cout << "/*===*" << std::endl;
			std::cout << " *" << std::endl;
			std::cout << " *" << std::endl;
			std::cout << " *" << std::endl;
#if 1
			std::cout << " *." << std::endl;
			std::cout << " *:" << std::endl;
			std::cout << " *;" << std::endl;
#endif
			std::cout << " *" << std::endl;
			std::cout << " *---*/" << std::endl;
			std::cout << std::endl << std::endl;
			break;
		}
	}
	return (c);
}

/*====================================================================*
 *
 *   signed statement (signed c);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ocblock::statement (signed c) 

{
	while (oascii::isspace (c)) 
	{
		c = ocblock::keep (c);
	}
	if (c == '{') 
	{
		this->mlevel++;
		c = ocblock::keep (c);
		c = ocblock::program (c, '}');
		c = ocblock::keep (c);
		this->mlevel--;
	}
	else if (c != ';') 
	{
		this->mlevel++;
		std::cout.put ('{');
		std::cout.put (' ');
		c = ocblock::program (c, ';');
		c = ocblock::keep (c);
		std::cout.put (' ');
		std::cout.put ('}');
		this->mlevel--;
	}
	return (c);
}


/*====================================================================*
 *
 *   signed condition (signed c);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ocblock::condition (signed c) 

{
	while (oascii::isspace (c)) 
	{
		c = ocblock::keep (c);
	}
	if (c == '(') 
	{
		c = ocblock::context ('(', ')');
	}
	else if (c != ';') 
	{
		this->mlevel++;
		std::cout.put (' ');
		std::cout.put ('(');
		c = ocblock::program (c, ';');
		c = ocblock::keep (c);
		std::cout.put (')');
		std::cout.put (' ');
		this->mlevel--;
	}
	return (c);
}

/*====================================================================*
 *
 *  signed program (signed c, signed e);
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed ocblock::program (signed c, signed e) 

{
	c = ocblock::preamble (c);
	while ((c != e) && (c != EOF)) 
	{
		if (c == '/') 
		{
			c = ocblock::comment (c);
			continue;
		}
		if (c == '#') 
		{
			c = ocblock::command ('#', '\n');
			continue;
		}
		if (c == '(') 
		{
			c = ocblock::context ('(', ')');
			continue;
		}
		if (c == '[') 
		{
			c = ocblock::context ('[', ']');
			continue;
		}
		if (c == '{') 
		{
			this->mlevel++;
			c = ocblock::keep (c);
			c = ocblock::program (c, '}');
			c = ocblock::keep (c);
			this->mlevel--;
			c = ocblock::preamble (c);
			continue;
		}
		if (oascii::isquote (c)) 
		{
			c = ocblock::literal (c);
			continue;
		}
		if (oascii::isalpha (c) || (c == '_')) 
		{
			char string [100];
			char *sp = string;
			do 
			{
				*sp++ = c;
				c = ocblock::keep (c);
			}
			while (oascii::isalnum (c) || (c == '_'));
			*sp = (char)(0);
			if ((c == '(') || (c == '[') || (c == '{')) 
			{
				std::cout.put (' ');
			}
			if (!strcmp (string, "if")) 
			{
				c = ocblock::condition (c);
				c = ocblock::statement (c);
				continue;
			}
			if (!strcmp (string, "else")) 
			{
				c = ocblock::statement (c);
				return (c);
			}
			if (!strcmp (string, "while")) 
			{
				c = ocblock::condition (c);
				c = ocblock::statement (c);
				continue;
			}
			if (!strcmp (string, "for")) 
			{
				c = ocblock::condition (c);
				c = ocblock::statement (c);
				continue;
			}
			if (!strcmp (string, "do")) 
			{
				c = ocblock::statement (c);
				continue;
			}
			if (!strcmp (string, "return")) 
			{
				c = ocblock::condition (c);
				continue;
			}
			if (!strcmp (string, "exit")) 
			{
				c = ocblock::condition (c);
				continue;
			}
			continue;
		}
		c = ocblock::keep (c);
	}
	return (e);
}


/*====================================================================*
 *
 *   ocblock ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ocblock::ocblock () 

{
	this->mlevel = 1;
	return;
}


/*====================================================================*
 *
 *   ocblock (signed level);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ocblock::ocblock (signed level) 

{
	this->mlevel = level;
	return;
}


/*====================================================================*
 *
 *   ~ocblock();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

ocblock::~ocblock () 

{
	return;
}


/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

