/*====================================================================*
 *
 *   bool makestate (RECYCLE *recycle, char const *filename);
 *
 *   search the state vector for the named file and return the index; 
 *   create an entry, if missing, and initialize the time to now; 
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

#ifndef MAKESTATE_SOURCE
#define MAKESTATE_SOURCE

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../recycle/recycle.h"

bool makestate (RECYCLE *recycle, char const *filename) 

{
	recycle->state = recycle->nstates++;
	recycle->states = realloc (recycle->states, recycle->nstates * sizeof (STATE));
	recycle->states [recycle->state].filename = strdup (filename);
	recycle->states [recycle->state].tm = recycle->tm;
	return (true);
}


#endif

