/*====================================================================*
 *
 *   LINK *freeitem (LINK * item, void *data, void  * func (void *, void *));
 *
 *   link.h
 *
 *   delete specified LINK item after deleting attached data;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FREEITEM_SOURCE
#define FREEITEM_SOURCE

#include <stdlib.h>

#include "../link/link.h"

LINK *freeitem (LINK * item, void *data, void *func (void *, void *)) 

{
	if (item) 
	{
		if (func) 
		{
			item->data = func (item->data, data);
		}
		free (item->name);
		free (item);
	}
	return ((LINK *) (0));
}


#endif

