/*====================================================================*
 *
 *   void xmlschema ();
 *
 *   nodes.h
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef XMLSCHEMA_SOURCE
#define XMLSCHEMA_SOURCE

#include "../nodes/nodes.h"
#include "../tools/markup.h"
#include "../tools/format.h"

void xmlschema () 

{
	unsigned margin = 0;
	indent (margin, "<?xml version='%s' encoding='%s'?>", XML_VERSION, XML_CHARSET);
	indent (margin++, "<xs:schema xmlns:xs='%s' elementFormDefault='%s'>", XML_SCHEMA, "qualified");
	indent (margin++, "<xs:element name='%s'>", DATA_OBJECT);
	indent (margin++, "<xs:complexType>");
	indent (margin, "<xs:attribute name='%s' use='optional' type='xs:NCName'/>", DATA_NAME);
	indent (margin, "<xs:attribute name='%s' use='optional' type='xs:string'/>", DATA_TEXT);
	indent (margin++, "<xs:sequence>");
	indent (margin, "<xs:element maxOccurs='unbounded' ref='%s'/>", DATA_MEMBER);
	indent (margin--, "</xs:sequence>");
	indent (margin--, "</xs:complexType>");
	indent (margin--, "</xs:element>");
	indent (margin++, "<xs:element name='%s'>", DATA_MEMBER);
	indent (margin++, "<xs:complexType>");
	indent (margin, "<xs:attribute name='%s' use='required' type='xs:NCName'/>", DATA_NAME);
	indent (margin, "<xs:attribute name='%s' use='optional' type='xs:string'/>", DATA_TEXT);
	indent (margin++, "<xs:sequence>");
	indent (margin++, "<xs:sequence>");
	indent (margin, "<xs:element ref='%s'/>", DATA_OFFSET);
	indent (margin, "<xs:element ref='%s'/>", DATA_LENGTH);
	indent (margin--, "</xs:sequence>");
	indent (margin++, "<xs:choice>");
	indent (margin, "<xs:element ref='%s'/>", DATA_STRUCT);
	indent (margin, "<xs:element ref='%s'/>", DATA_STRING);
	indent (margin, "<xs:element ref='%s'/>", DATA_BYTE);
	indent (margin--, "</xs:choice>");
	indent (margin--, "</xs:sequence>");
	indent (margin--, "</xs:complexType>");
	indent (margin--, "</xs:element>");
	indent (margin, "<xs:element name='%s' type='xs:positiveInteger'/>", DATA_LENGTH);
	indent (margin, "<xs:element name='%s' type='xs:hexBinary'/>", DATA_OFFSET);
	indent (margin++, "<xs:element name='%s'>", DATA_STRUCT);
	indent (margin++, "<xs:complexType>");
	indent (margin, "<xs:attribute name='%s' use='optional' type='xs:NCName'/>", DATA_NAME);
	indent (margin, "<xs:attribute name='%s' use='optional' type='xs:string'/>", DATA_TEXT);
	indent (margin++, "<xs:choice maxOccurs='unbounded'>");
	indent (margin, "<xs:element ref='%s'/>", DATA_BYTE);
	indent (margin, "<xs:element ref='%s'/>", DATA_MEMORY);
	indent (margin--, "</xs:choice>");
	indent (margin--, "</xs:complexType>");
	indent (margin--, "</xs:element>");
	indent (margin, "<xs:element name='%s' type='xs:string'/>", DATA_STRING);
	indent (margin, "<xs:element name='%s' type='xs:hexBinary'/>", DATA_MEMORY);
	indent (margin, "<xs:element name='%s' type='xs:unsignedByte'/>", DATA_BYTE);
	indent (margin--, "</xs:schema>");
	return;
}


#endif

