/*====================================================================*
 *
 *   void *_malloc(size_t nbytes);
 *
 *   _malloc.h
 *
 *   This function allocates a contiguous memory region of specified
 *   size, in bytes, and returns the address aligned to an 'unsigned
 *   int' boundary. NULL is returned if a region cannot be allocated.
 *
 *   Regions are not purged and therefore, may contain garbage.
 *
 *   This algorithm is a modified version of one presented in "The C
 *   Programming Language" by Kernighan and Ritchie.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "../stdlib/_malloc.h"
#include "../stdlib/_stddef.h"

void * _malloc (size_t nbytes) 

{
	extern Pool * head;
	unsigned nalloc;
	register Pool * p;
	register Pool * q;
	for (q = head; q != NULL; q = p) 
	{
		p = q->_ptr;
		if (p->_cnt == nbytes) 
		{
			q->_ptr = p->_ptr;
			p->_ptr = p;
			head = q;
			return ((char *)(++p));
		}
		if (p->_cnt > nbytes) 
		{
			p->_cnt -= nbytes;
			p += p->_cnt;
			p->_cnt = nbytes;
			head = q;
			return ((char *)(++p));
		}
		if (p == head) 
		{
			nalloc = (_NALLOC) * ((nbytes * sizeof (Pool) + ((_NALLOC)-1)) / (_NALLOC));
			if ((long)(p = (Pool *)(_sbrk (nalloc))) == (-1)) 
			{
				break;
			}
			p->_ptr = p;
			p->_cnt = nalloc/sizeof (Pool);
			_free ((unsigned short int *)(++p));
			p = head;
		}
	}
	return (NULL);
}

