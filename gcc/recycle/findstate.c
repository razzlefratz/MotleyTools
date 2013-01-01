/*====================================================================*
 *
 *   bool findstate (RECYCLE *recycle, char const *filename);
 *
 *   search the state vector for the named file; return true if the 
 *   file is present or false if missing; on success, recycle->state 
 *   is aligned to the matching state;
 * 
 *   the state vector contains filenames and their rotation dates; it 
 *   is read from the state file before and written to the state file
 *   after rotation; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef FINDSTATE_SOURCE
#define FINDSTATE_SOURCE

#include <string.h>

#include "../recycle/recycle.h"

bool findstate (RECYCLE *recycle, char const *filename) 

{
	for (recycle->state = 0; recycle->state < recycle->nstates; recycle->state++) 
	{
		if (strcmp (filename, recycle->states [recycle->state].filename) == 0) 
		{
			return (true);
		}
	}
	return (false);
}


#endif

