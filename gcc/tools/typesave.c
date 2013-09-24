/*====================================================================*
 *
 *   void typesave (struct _type_ const list [], size_t size, char const * name);
 *
 *   save struct _type_ list[] as C Preprocessor define statements 
 *   plus a table declaration;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef TYPESAVE_SOURCE
#define TYPESAVE_SOURCE

#include <stdio.h>
#include <errno.h>

#include "../tools/tools.h"
#include "../tools/markup.h"
#include "../tools/format.h"
#include "../tools/error.h"

void typesave(struct _type_ const list[], size_t size, char const * name, flag_t flags)

{
	size_t item;
	for (item = 1; item < size; item++)
	{
		if (list[item].type == list[item - 1].type)
		{
			error (1, EINVAL, "item %zu is a duplicate", item);
		}
		if (list[item].type < list[item - 1].type)
		{
			error (1, EINVAL, "item %zu is out of order", item);
		}
	}
	if (flags & TOOLS_B_DEFINE)
	{
		printf ("/*=*\n *   constants;\n *-*/\n\n");
		for (item = 0; item < size; item++)
		{
			printf ("#define %s 0x%04X\n", list[item].name, list[item].type);
		}
		printf ("\n");
	}
	if (flags & TOOLS_B_DECLARE)
	{
		printf ("/*=*\n *   constants;\n *-*/\n\n");

#if 0

		printf ("#define %sS %zu\n", name, size);

#else

		printf ("#define %sS (sizeof (%s) / sizeof (%s [0]))\n", name, name, name);

#endif

		printf ("\n/*=*\n *   variables;\n *-*/\n\n");

#if 0

		printf ("static struct _type_ %s [%sS] = \n\n{\n", name, name);

#else

		printf ("static struct _type_ %s [] = \n\n{\n", name);

#endif

		for (item = 0; item < size; item++)
		{
			if (flags & TOOLS_B_NUMBER)
			{
				printf ("\t{\n\t\t0x%04X,\n\t\t\"%s\"\n\t},\n", list[item].type, list[item].name);
			}
			else 
			{
				printf ("\t{\n\t\t%s,\n\t\t\"%s\"\n\t},\n", list[item].name, list[item].name);
			}
		}
		printf ("};\n\n");
	}
	if (flags & TOOLS_B_SWITCH)
	{
		signed margin = 1;
		printf ("/*=*\n *   variables;\n *-*/\n\n");
		indent (margin, "switch (type)");
		indent (margin, "{");
		for (item = 0; item < size; item++)
		{
			if (flags & TOOLS_B_NUMBER)
			{
				indent (margin++, "case 0x%04X:", list[item].type);
				indent (margin--, "break;");
			}
			else 
			{
				indent (margin++, "case %s:", list[item].name);
				indent (margin--, "break;");
			}
		}
		indent (margin++, "default:");
		indent (margin--, "break;");
		indent (margin, "}\n");
	}
	if (flags & TOOLS_B_MARKUP)
	{
		signed margin = 1;
		indent (margin++, "<h2>");
		indent (margin, "%s", name);
		indent (margin--, "</h2>");
		indent (margin++, "<table class='%s'>", STYLE_DATA);
		indent (margin++, "<tr>");
		indent (margin++, "<th class='%s'>", STYLE_NAME);
		indent (margin, "Symbol");
		indent (margin--, "</th>");
		indent (margin++, "<th class='%s'>", STYLE_SIZE);
		indent (margin, "Value");
		indent (margin--, "</th>");
		indent (margin++, "<th class='%s'>", STYLE_TEXT);
		indent (margin, "Description");
		indent (margin--, "</th>");
		indent (margin--, "</tr>");
		for (item = 0; item < size; item++)
		{
			indent (margin++, "<tr>");
			indent (margin++, "<td class='%s'>", STYLE_NAME);
			indent (margin, "%s", list[item].name);
			indent (margin--, "</td>");
			indent (margin++, "<td class='%s'>", STYLE_SIZE);
			indent (margin, "0x%04X", list[item].type);
			indent (margin--, "</td>");
			indent (margin++, "<td class='%s'>", STYLE_TEXT);
			indent (margin, "&nbsp;");
			indent (margin--, "</td>");
			indent (margin--, "</tr>");
		}
		indent (margin--, "</table>");
	}
	return;
}

#endif



