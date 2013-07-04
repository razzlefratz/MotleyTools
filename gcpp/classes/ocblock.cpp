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
		c = ocblock::feed (c);
	}
	if (c == '{') 
	{
		c = ocblock::feed (c);
		c = ocblock::program (c, '}');
		c = ocblock::feed (c);
	}
	else if (c != ';') 
	{
		std::cout.put ('{');
		std::cout.put (' ');
		c = ocblock::program (c, ';');
		c = ocblock::feed (c);
		std::cout.put (' ');
		std::cout.put ('}');
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
		c = ocblock::feed (c);
	}
	if (c == '(') 
	{
		c = ocblock::context ('(', ')');
	}
	else if (c != ';') 
	{
		std::cout.put ('(');
		c = ocblock::context (c, ';');
		std::cout.put (')');
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
			c = ocblock::feed (c);
			c = ocblock::program (c, '}');
			c = ocblock::feed (c);
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
			char * sp = string;
			do
			{
				* sp++ = c;
				c = ocblock::feed (c);
			}
			while (oascii::isalnum (c) || (c == '_'));
			* sp = (char)(0);
			if ((c == '(') || (c == '[') || (c == '{')) 
			{
				std::cout.put (' ');
			}
			if (!std::strcmp (string, "if")) 
			{
				c = ocblock::condition (c);
				c = ocblock::statement (c);
				continue;
			}
			if (!std::strcmp (string, "else")) 
			{
				c = ocblock::statement (c);
				continue;
			}
			if (!std::strcmp (string, "while")) 
			{
				c = ocblock::condition (c);
				c = ocblock::statement (c);
				continue;
			}
			if (!std::strcmp (string, "for")) 
			{
				c = ocblock::condition (c);
				c = ocblock::statement (c);
				continue;
			}
			if (!std::strcmp (string, "do")) 
			{
				c = ocblock::statement (c);
				continue;
			}
			if (!std::strcmp (string, "return")) 
			{
				c = ocblock::condition (c);
				continue;
			}
			if (!std::strcmp (string, "exit")) 
			{
				c = ocblock::condition (c);
				continue;
			}
			continue;
		}
		c = ocblock::feed (c);
	}
	return (c);
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

