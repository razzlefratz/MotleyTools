/*====================================================================*
 *
 *   signed delay (unsigned seconds);
 *
 *--------------------------------------------------------------------*/

#ifndef DELAY_SOURCE
#define DELAY_SOURCE

#include <stdint.h>
#include <unistd.h>
#include <memory.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>

#include "../tools/error.h"

void delay (unsigned seconds) 

{
	struct timeval initial;
	struct timeval current;
	unsigned timer = 0;
	if (gettimeofday (&initial, (struct timezone *)(0)) == -1) 
	{
		error (1, errno, "function %s can't set timer", __func__);
	}
	for (timer = 0; timer < seconds; timer = (current.tv_sec - initial.tv_sec) + ((current.tv_usec - initial.tv_usec) / 1000000)) 
	{

/*
 *	do something that takes some time;
 */

		if (gettimeofday (&current, (struct timezone *)(0)) == -1) 
		{
			error (1, errno, "function %s can't reset timer", __func__);
		}
	}
	return;
}


#endif

