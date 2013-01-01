/*====================================================================*
 *
 *   void isort(void const *list[], size_t size, int comp(void const *, void const *), void swap(void const *[], size_t, size_t), void sift(void const *[], size_t, size_t, int comp(void const *, void const *), void swap(void const *[], size_t, size_t)));
 *
 *   sort.h
 *
 *   arrange elements of an unordered list using an 'insertion' or
 *   'bridge player' sort algorithm;
 *
 *   an insertion sort is the most compact of all the sort algorithms; it
 *   is very fast when items are in order and very slow when items are in
 *   reverse order; it is a special case of an 'increment sort' where the
 *   interval is 1;
 *
 *   although it is not the fastest under all circumstances, it exhibits
 *   reasonable speed under a wide variety of circumstances and is ideal
 *   for small sorting tasks;
 *
 *   For more information on this sort algorithm read about Algorithm S
 *   in "Sorting and Searching" by Donald Knuth.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef ISORT_SOURCE
#define ISORT_SOURCE

#include "../sort/sort.h"

void isort (void const *list [], size_t size, int comp (void const *, void const *), void swap (void const *[], size_t, size_t), void sift (void const *[], size_t, size_t, int comp (void const *, void const *), void swap (void const *[], size_t, size_t))) 

{
	size_t item = 0;
	while (++item < size) 
	{
		sift (list, item, 1, comp, swap);
	}
	return;
}


#endif

