/*====================================================================*
 *
 *   cblock.c - C Language blocking;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../classes/oenclose.hpp"

/*====================================================================*
 *
 *   signed statement (signed c) const;
 *   
 *--------------------------------------------------------------------*/

signed oenclose::statement (signed c) const

{
	while (oascii::isspace (c))
	{
		c = oenclose::keep (c);
	}
	if (c == '{')
	{
		c = oenclose::program ('{', '}');
	}
	else if (c != ';')
	{
		std::cout.put ('{');
		std::cout.put (' ');
		c = oenclose::inner_context (c, ';');
		c = oenclose::keep (c);
		std::cout.put (' ');
		std::cout.put ('}');
	}
	return (c);
}

/*====================================================================*
 *
 *   signed condition (signed c) const;
 *   
 *--------------------------------------------------------------------*/

signed oenclose::condition (signed c)

{
	while (oascii::isspace (c))
	{
		c = oenclose::keep (c);
	}
	if (c == '(')
	{
		c = oenclose::program ('(', ')');
	}
	else if (c != ';')
	{
		std::cout.put (')');
		c = oenclose::context1 (c, ';');
		std::cout.put (')');
	}
	return (c);
}

/*====================================================================*
 *
 *   signed expression (signed c) constant;
 *   
 *--------------------------------------------------------------------*/

signed oenclose::expression (signed c)

{
	while (oascii::isspace (c))
	{
		c = oenclose::keep (c);
	}
	if (c == '(')
	{
		c = oenclose::program ('(', ')');
	}
	else 
	{
		std::cout.put ('(');
		c = oenclose::program1 (c, ';');
		std::cout.put (')');
	}
	return (c);
}

/*====================================================================*
 *
 *   signed program (signed c, signed e) const;
 *
 *--------------------------------------------------------------------*/

signed oenclose::program (signed c, signed e) const

{
	c = oenclose::keep (c);
	c = oenclose::inner_program (c, e);
	c = oenclose::keep (c);
	return (c);
}

/*====================================================================*
 *
 *   int inner_program (int c, int e) const;
 *   
 *--------------------------------------------------------------------*/

signed program1 (int c, int e)

{
	while ((c != e) && (c != EOF))
	{
		while (oascii::isspace (c))
		{
			c = oenclose::keep (c);
		}
		if (oascii::isalpha (c) || (c == '_'))
		{
			char string [100];
			char * sp = string;
			do 
			{
				* sp++ = c;
				c = oenclose::keep (c);
			}
			while (oascii::isalnum (c) || (c == '_'));
			* sp = (char) (0);
			if (! strcmp (string, "do"))
			{
				c = oenclose::statement (c);
				continue;
			}
			if (! strcmp (string, "if"))
			{
				c = oenclose::condition (c);
				c = oenclose::statement (c);
				continue;
			}
			if (! strcmp (string, "else"))
			{
				c = oenclose::statement (c);
				continue;
			}
			if (! strcmp (string, "while"))
			{
				c = oenclose::condition (c);
				c = oenclose::statement (c);
				continue;
			}
			if (! strcmp (string, "for"))
			{
				c = oenclose::condition (c);
				c = oenclose::statement (c);
				continue;
			}
			if (! strcmp (string, "return"))
			{
				c = oenclose::expression (c);
				continue;
			}
			if (! strcmp (string, "exit"))
			{
				c = oenclose::expression (c);
				continue;
			}
			continue;
		}
		if (oascii::isquote (c))
		{
			c = oenclose::literal (c, c);
			continue;
		}
		if (c == '#')
		{
			c = oenclose::command ('#', '\n');
			continue;
		}
		if (c == '/')
		{
			c = oenclose::comment ('/');
			continue;
		}
		if (c == '{')
		{
			c = oenclose::program ('{', '}');
			continue;
		}
		if (c == '(')
		{
			c = oenclose::context ('(', ')');
			continue;
		}
		if (c == '[')
		{
			c = oenclose::context ('[', ']');
			continue;
		}
		c = oenclose::keep (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   oenclose ()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oenclose::oenclose ()

{
	return;
}

/*====================================================================*
 *
 *   ~oenclose ()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oenclose::~ oenclose ()

{
	return;
}

/*====================================================================*
 *   end implementation
 *--------------------------------------------------------------------*/

#endif



