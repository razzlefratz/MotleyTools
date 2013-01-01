/*====================================================================*
 *
 *   nodes.h - document node definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 2001-2006 by Charles Maier Associates Limited;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef NODES_HEADER
#define NODES_HEADER

/*====================================================================*
 *   system headers;
 *--------------------------------------------------------------------*/

#include <stdint.h>
#include <unistd.h>

/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/

#define NODE_ROOT 0
#define NODE_PATH 0

#define NODE_ELEM '<'
#define NODE_SGML '!' 
#define NODE_PROC '?' 
#define NODE_CODE '%' 
#define NODE_ATTR ' '
#define NODE_QUOT '"' 
#define NODE_VALU '=' 
#define NODE_ETAG '/' 
#define NODE_OTAG '*' 
#define NODE_DATA '>' 

#define DATA_SCHEMA "data.xsd"
#define DATA_NAME "name"
#define DATA_TEXT "text"
#define DATA_OBJECT "object"
#define DATA_MEMBER "member"
#define DATA_OFFSET "offset"
#define DATA_LENGTH "length"
#define DATA_STRUCT "struct"
#define DATA_STRING "string"
#define DATA_MEMORY "memory"
#define DATA_HUGE "huge"
#define DATA_LONG "long"
#define DATA_WORD "word"
#define DATA_BYTE "byte"

/*====================================================================*
 *   variables;
 *--------------------------------------------------------------------*/

typedef struct node 

{
	struct node * above;
	struct node * prior;
	struct node * after;
	struct node * below;
	unsigned level;
	unsigned index;
	unsigned count;
	unsigned line;
	unsigned type;
	char * text;
}

NODE;

/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/

char const * xmlselect (struct node const *, char const * element, char const * attribute);
struct node const * _xmlattribute (struct node const *);
struct node const * _xmlvalue (struct node const *);
void xmlstream (struct node const *);
void xmlindent (struct node const *);
void xmltree (struct node const *);
struct node * nodes (struct node *, unsigned index);
struct node * xmlnode (struct node *);
struct node * xmlopen (char const * filename);
struct node const * xmlelement (struct node const *, char const * name);
struct node const * xmlattribute (struct node const *, char const * name);
struct node const * xmlvalue (struct node const *);
struct node const * xmlcontent (struct node const *);
signed xmledit (struct node *, void * memory, size_t extent);
signed xmlread (struct node *, char const * filename);
void xmlscan (struct node *);
void xmlfree (struct node *);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

void reorder (struct node * node);
unsigned nodesize (struct node * node);
void xmlschema ();
void xmlsample ();

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

