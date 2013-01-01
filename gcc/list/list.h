/*====================================================================*
 *
 *   list.h - 
 *
 *.  Motley Tools by Charles Maier
 *:  modified thu 11 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LIST_HEADER
#define LIST_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   constant definitions; 
 *--------------------------------------------------------------------*/

#define LIST_COLUMNS 80
#define LIST_SPACING 2

/*====================================================================*
 *   variable declarations;
 *--------------------------------------------------------------------*/

typedef struct _list_ 

{
	char const **table;
	signed order;
	signed error;
	flag_t flags;
	size_t block;
	size_t limit;
	size_t start;
	size_t count;
	size_t index;
	size_t lower;
	size_t upper;
	size_t point;
}

LIST;

/*====================================================================*
 *   function declarations;
 *--------------------------------------------------------------------*/

void listload (LIST *, char const * filename, char buffer [], size_t length);
bool listsort (LIST *);
bool listcreate (LIST *, size_t size);
bool listdetect (LIST *, char const *);
bool listremove (LIST *, char const *);
bool listinsert (LIST *, char const *);
bool listappend (LIST *, char const *);
bool listdefine (LIST *, char const *, char const c);
void listcolumn (LIST *, FILE *, unsigned width, unsigned count, bool index);
bool liststatus (LIST *, FILE *);
bool listrubout (LIST *);
bool listexpand (LIST *);
bool listdelete (LIST *);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif

