/*====================================================================*
 *
 *   signed close_ll (struct channel * channel);
 *
 *   channel.h
 *
 *   close a raw ethernet packet channel in on a Linux platform;
 *
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>;
 *:  Published 2005 by Charles Maier Associates Limited;
 *;  Released under the GNU General Public Licence v2 and later;
 *
 *--------------------------------------------------------------------*/

#ifndef CLOSE_LL_SOURCE
#define CLOSE_LL_SOURCE

#include <unistd.h>

#include "../ether/channel.h"
 
signed close_ll (struct channel * channel) 

{
	close (channel->fd);
	channel->fd = -1;
	return (0);
}

#endif
 

