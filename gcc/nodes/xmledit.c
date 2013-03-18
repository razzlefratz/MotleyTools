/*====================================================================*
 *
 *   xmledit.c -
 *
 *   nodes.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef XMLEDIT_SOURCE
#define XMLEDIT_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>

/*====================================================================*
 *  custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/number.h"
#include "../tools/memory.h"
#include "../tools/error.h"
#include "../nodes/nodes.h"

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

static char const * member = "";
static char const * string = "";
static size_t offset = 0;
static size_t length = 0;
static unsigned bailout = 1;
static bool series = false;

/*====================================================================*
 *
 *   void position (char const * format, char const * string, size_t extent);
 *   
 *   sanity check offset and extent before editing memory;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void position (char const * format, size_t extent) 

{
	if (!length) 
	{
		error (bailout, EINVAL, "member %s %s %s has no extent", member, format, string);
	}
	if (offset > extent) 
	{
		error (bailout, EINVAL, "member %s offset (0x%04zX) exceeds memory extent (0x%04zX)", member, offset, extent);
	}
	if ((offset + length) > extent) 
	{
		error (bailout, EINVAL, "member %s extent (0x%04zX) exceeds memory extent (0x%04zX)", member, offset + length, extent);
	}
	return;
}


/*====================================================================*
 *
 *   signed _xmlinteger (unsigned radix);
 *
 *   convert numeric string to an unsigned integer; all string digits
 *   string digits must be valid for the specifid radix; radix can be
 *   1 through 16 but 2, 8, 10 and 16 are the only sensible choices;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static unsigned _xmlinteger (unsigned radix) 

{
	unsigned digit;
	unsigned myvalue = 0;
	while ((digit = todigit (*string)) < radix) 
	{
		myvalue *= radix;
		myvalue += digit;
		string++;
	}
	if (*string) 
	{
		error (bailout, EINVAL, "%s %s is not an number", DATA_MEMBER, member);
	}
	return (myvalue);
}


/*====================================================================*
 *
 *   void _xmlstring (void * memory, size_t extent);
 *   
 *   _xmlstring is expressed as character text;  truncate string and
 *   pad memory with NULs as needed;
 *
 *   per the schema, an series cannot have a string member;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void _xmlstring (void * memory, size_t extent) 

{
	char * buffer = (char *)(memory);
	if (series) 
	{
		error (bailout, EINVAL, "%s %s found inside %s", DATA_MEMBER, member, DATA_STRUCT);
	}
	if (length) 
	{
		while (length > 1) 
		{
			if (isprint (*string)) 
			{
				buffer [offset] = *string++;
			}
			else 
			{
				buffer [offset] = (char) (0);
			}
			offset++;
			length--;
		}
		buffer [offset] = (char)(0);
		offset++;
		length--;
	}
	return;
}


/*====================================================================*
 *
 *   void _xmlmemory (void * memory, size_t extent);
 *   
 *   _xmlmemory is a hexadecimal string of variable extent; an empty 
 *   string increments offset and decrements length but nothing is
 *   written to the memory;
 *   
 *   per the schema, if _xmlmemory is not inside an series then it must
 *   match the object extent;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void _xmlmemory (void * memory, size_t extent) 

{
	uint8_t * buffer = (uint8_t *)(memory);
	if (!*string) 
	{
		offset++;
		length--;
	}
	while ((*string) && (length)) 
	{
		uint8_t msb = todigit (*string++);
		uint8_t lsb = todigit (*string++);
		if ((msb > 0x0F) || (lsb > 0x0F)) 
		{
			error (bailout, EINVAL, "%s %s is not hexadecimal", DATA_MEMBER, member);
		}
		buffer [offset] = (msb << 4) + lsb;
		offset++;
		length--;
	}
	if ((length) && (!series)) 
	{
		error (bailout, EINVAL, "%s %s is too short", DATA_MEMBER, member);
	}
	if (*string) 
	{
		error (bailout, EINVAL, "%s %s is too long", DATA_MEMBER, member);
	}
	return;
}


/*====================================================================*
 *
 *   void _xmlnumber (void * memory, size_t extent);
 *   
 *   _xmlnumber is a decimal integer string of variable length; the
 *   value cannot exceed length bytes and offset is incremented by
 *   length bytes;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void _xmlnumber (void * memory, size_t extent) 

{
	uint64_t number = 0;
	uint64_t maximum = 0;
	maximum = ~maximum;
	if (length < sizeof (uint64_t)) 
	{
		maximum <<= (length << 3);
		maximum = ~maximum;
	}
	while (isdigit (*string)) 
	{
		number *= 10;
		number += *string - '0';
		if (number > maximum) 
		{
			error (bailout, EINVAL, "%s %s exceeds %zd bytes", DATA_MEMBER, member, length);
		}
		string++;
	}
	if (*string) 
	{
		error (bailout, EINVAL, "%s %s is not decimal", DATA_MEMBER, member);
	}
	memcpy ((uint8_t *)(memory) + offset, &number, length);

#if 0

	endian (memory + offset, length);

#endif

	offset += length;
	length -= length;
	return;
}


/*====================================================================*
 *
 *   void _xmlbyte (void * memory, size_t extent);
 *   
 *   _xmlbyte is a decimal integer string of variable extent; the
 *   value cannot exceed 255; an empty string increments offset and 
 *   decrements length but nothing is written to the memory;
 *   
 *   per the schema, if _xmlbyte is not inside an series then it must
 *   it must match the object extent which must be 1 by implication;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static void _xmlbyte (void * memory, size_t extent) 

{
	if (*string) 
	{
		uint16_t number = 0;
		while (isdigit (*string)) 
		{
			number *= 10;
			number += *string - '0';
			if (number > 0xFF) 
			{
				error (bailout, EINVAL, "%s %s exceeds 8 bits", DATA_MEMBER, member);
			}
			string++;
		}
		if (*string) 
		{
			error (bailout, EINVAL, "%s %s is not decimal", DATA_MEMBER, member);
		}
		memcpy ((uint8_t *)(memory) + offset, &number, sizeof (uint8_t));
	}
	offset++;
	length--;
	if ((length) && (!series)) 
	{
		error (bailout, EINVAL, "%s %s is too short", DATA_MEMBER, member);
	}
	return;
}


/*====================================================================*
 *
 *   char const * content (NODE * node);
 *
 *   nodes.h
 *
 *   return node content as a string or NIL if nodes.has no content;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static char const * _xmlcontent (NODE * node) 

{
	if (node) 
	{
		node = node->below;
	}
	while (node) 
	{
		if (node->type == NODE_DATA) 
		{
			return (node->text);
		}
		node = node->after;
	}
	return ("");
}


/*====================================================================*
 *
 *   char const * myvalue (NODE * node);
 *
 *   nodes.h
 *
 *   return node value as a string or NIL if nodes.has no value;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

static char const * myvalue (NODE * node) 

{
	if (node) 
	{
		node = node->below;
	}
	while (node) 
	{
		if (node->type == NODE_VALU) 
		{
			return (node->text);
		}
		node = node->after;
	}
	return ("");
}


/*====================================================================*
 *
 *   char const * myattribute (NODE * node, char const * name);
 *
 *   nodes.h
 *   
 *   search node for the named attribute; return the attribute value
 *   as a string or NIL if attribute is missing;
 *   
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *   
 *--------------------------------------------------------------------*/

static char const * myattribute (NODE * node, char const * name) 

{
	if (node) 
	{
		node = node->below;
	}
	while (node) 
	{
		if (node->type == NODE_ATTR) 
		{
			if (!strcmp (node->text, name)) 
			{
				name = myvalue (node);
				return (name);
			}
		}
		node=node->after;
	}
	return ("");
}


/*====================================================================*
 *
 *   signed xmledit (NODE * node, void * memory, size_t extent);
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed xmledit (NODE * node, void * memory, size_t extent) 

{
	if (node) 
	{
		node = node->below;
	}
	while (node) 
	{
		if (node->type == NODE_ELEM) 
		{
			if (!strcmp (node->text, DATA_MEMBER)) 
			{
				member = myattribute (node, DATA_NAME);
				offset = (unsigned)(-1);
				length = (unsigned)(-1);
				series = false;
			}
			else if (!strcmp (node->text, DATA_OFFSET)) 
			{
				string = _xmlcontent (node);
				offset = _xmlinteger (16);
			}
			else if (!strcmp (node->text, DATA_LENGTH)) 
			{
				string = _xmlcontent (node);
				length = _xmlinteger (10);
			}
			else if (!strcmp (node->text, DATA_STRUCT)) 
			{
				series = true;
			}
			else if (!strcmp (node->text, DATA_STRING)) 
			{
				string = _xmlcontent (node);
				position (node->text, extent);
				_xmlstring (memory, extent);
			}
			else if (!strcmp (node->text, DATA_MEMORY)) 
			{
				string = _xmlcontent (node);
				position (node->text, extent);
				_xmlmemory (memory, extent);
			}
			else if (!strcmp (node->text, DATA_HUGE)) 
			{
				length = sizeof (uint64_t);
				position (node->text, extent);
				string = _xmlcontent (node);
				_xmlnumber (memory, extent);
			}
			else if (!strcmp (node->text, DATA_LONG)) 
			{
				length = sizeof (uint32_t);
				position (node->text, extent);
				string = _xmlcontent (node);
				_xmlnumber (memory, extent);
			}
			else if (!strcmp (node->text, DATA_WORD)) 
			{
				length = sizeof (uint16_t);
				position (node->text, extent);
				string = _xmlcontent (node);
				_xmlnumber (memory, extent);
			}
			else if (!strcmp (node->text, DATA_BYTE)) 
			{
				position (node->text, extent);
				string = _xmlcontent (node);
				_xmlbyte (memory, extent);
			}
			xmledit (node, memory, extent);
		}
		node = node->after;
	}
	return (0);
}


/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

