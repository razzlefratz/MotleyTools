/*====================================================================*
 *
 *   list.h - link list definitions and declarations;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef LINK_HEADER
#define LINK_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stddef.h>

/*====================================================================*
 * declare item structure
 *--------------------------------------------------------------------*/

typedef struct _link_ 

{
	struct _link_ * next;
	void * name;
	void * data;
}

LINK;

/*====================================================================*
 * basic stack functions for linear linked list items;
 *--------------------------------------------------------------------*/

size_t stacksize (LINK * list);
LINK *stackclear (LINK * list);
LINK *stackpush (LINK * list, void const *name, void const *data);
LINK *stackpop (LINK * list);

/*====================================================================*
 * declare item structure
 *--------------------------------------------------------------------*/

LINK *makeitem (void const *name, void const *data);
LINK *freeitem (LINK * item, void * data, void * func (void *, void *));
LINK *finditem (LINK * item, void const * name, int comp (void const *, void const *));
void walklist (LINK * item, void * data, void func (void *, void *));
void walkloop (LINK * item, void * data, void func (void *, void *));
unsigned listsize (LINK * item);

/*====================================================================*
 *   classic queue functions;
 *--------------------------------------------------------------------*/

LINK *queue (LINK * list, LINK * item);
LINK *enque (LINK * list, LINK * item);
LINK *deque (LINK * list);

/*====================================================================*
 *   classic queue function macros
 *--------------------------------------------------------------------*/

#define _append(list,item) list = queue(list,item)
#define _push(list,item)   list = queue(item,list)
#define _pop(list,item)    item = queue(list,list->link)

/*====================================================================*
 * end definitions;
 *--------------------------------------------------------------------*/

#endif

