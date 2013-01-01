/*====================================================================*
 *
 *   sort.h - basic sort/search constants and function definitions;
 *
 *   these functions are part of a collection that illustrates the modular
 *   nature of sorting algorithms; the collection implements common sorting
 *   algorithms by isolating sort strategy from compare and exchange logic
 *
 *   the comp and swap functions are user defined and must conform to the
 *   comp and swap function prototypes in sort.h; thus all the algorithms
 *   remain independent of the objects they sort;
 *
 *.  Motley Tools by Charles Maier
 *:  modified sun 07 sep 03 by user root on host zeus;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef SORT_HEADER
#define SORT_HEADER

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stddef.h>

/*====================================================================*
 *   declare custom search/sort function prototypes;
 *--------------------------------------------------------------------*/

size_t vfirst (void const *item, void const *list [], size_t size, int comp (void const *, void const *));
size_t vfinal (void const *item, void const *list [], size_t size, int comp (void const *, void const *));
size_t vindex (void const *item, void const *list [], size_t size, int comp (void const *, void const *));

#if 0

void qsort (void const *list [], size_t size, int comp (void const *, void const *));
void psort (void const *list [], size_t size, int comp (void const *, void const *), void swap (void const *[], size_t, size_t));

#endif

void isort (void const *list [], size_t size, int comp (void const *, void const *), void swap (void const *[], size_t, size_t), void sift (void const *[], size_t, size_t, int comp (void const *, void const *), void swap (void const *[], size_t, size_t)));
void ssort (void const *list [], size_t size, int comp (void const *, void const *), void swap (void const *[], size_t, size_t), void sift (void const *[], size_t, size_t, int comp (void const *, void const *), void swap (void const *[], size_t, size_t)));
void hsort (void const *list [], size_t size, int comp (void const *, void const *), void swap (void const *[], size_t, size_t));
void adheap (void const *list [], size_t size, int comp (void const *, void const *), void swap (void const *[], size_t, size_t));
void reheap (void const *list [], size_t size, int comp (void const *, void const *), void swap (void const *[], size_t, size_t));
void enheap (void const *list [], size_t size, int comp (void const *, void const *), void swap (void const *[], size_t, size_t));
void deheap (void const *list [], size_t size, int comp (void const *, void const *), void swap (void const *[], size_t, size_t));
void sift (void const *list [], size_t size, size_t step, int comp (void const *, void const *), void swap (void const *[], size_t, size_t));
void swap (void const *list [], size_t, size_t);

/*====================================================================*
 *    end definitions;
 *--------------------------------------------------------------------*/

#endif

