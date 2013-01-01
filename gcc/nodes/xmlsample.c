/*====================================================================*
 *
 *   void xmlsample ();
 *
 *   nodes.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef XMLSAMPLE_SOURCE
#define XMLSAMPLE_SOURCE

#include "../nodes/nodes.h"
#include "../tools/markup.h"
#include "../tools/format.h"

void xmlsample () 

{
	unsigned margin = 0;
	indent (margin++, "<%s xmlns:xsi='%s' xsi:noNamespaceSchemaLocation='%s'>", DATA_OBJECT, XML_NAMESPACE, DATA_SCHEMA);
	indent (margin++, "<%s %s='sample' %s='0000' %s='0'>", DATA_MEMBER, DATA_NAME, DATA_OFFSET, DATA_LENGTH);
	indent (margin--, "</%s>", DATA_MEMBER);
	indent (margin--, "</%s>", DATA_OBJECT);
	return;
}


#endif

