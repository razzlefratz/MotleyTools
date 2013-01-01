/*====================================================================*
 *
 *   int _free(void *memory);
 *
 *   This function releases a memory region previously acquired via
 *   malloc() or calloc(). Memory contents are not modified. NULL is
 *   is returned.
 *
 *   To maintain consistancy with other implementations, free() should
 *   be used with malloc() and cfree() with calloc().
 *
 *   This algorithm is a modified version of one presented in "The C
 *   Programming Language" by Kernighan and Ritchie.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_malloc.h"
#include "_stddef.h"

void _free (register void *buffer) 

{
	extern Pool *head;
	if (buffer) 
	{
		register Pool *p = buffer;
		register Pool *q = head;
		for (--p; !((p > q) && (p < q->_ptr)); q = q->_ptr) 
		{
			if ((q >= q->_ptr) && ((p > q) || (p < q->_ptr))) break;
		}
		if ((p + p->_cnt) == q->_ptr) 
		{
			p->_cnt += (q->_ptr)->_cnt;
			p->_ptr = (q->_ptr)->_ptr;
		}
		else p->_ptr = q->_ptr;
		if ((q + q->_cnt) == p) 
		{
			q->_cnt += p->_cnt;
			q->_ptr = p->_ptr;
		}
		else q->_ptr = p;
		head = q;
	}
	return;
}

