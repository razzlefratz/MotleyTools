/*====================================================================*
 *
 *   socket_ll.h - 
 *
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>;
 *:  Published 2005 by Charles Maier Associates Limited;
 *;  Released under the GNU General Public Licence v2 and later;
 *
 *--------------------------------------------------------------------*/

#ifndef SOCKET_LL_HEADER
#define SOCKET_LL_HEADER
 
/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <netpacket/packet.h>
 
/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"
 
/*====================================================================*
 *
 *--------------------------------------------------------------------*/
 
signed bind_ll (const char * interface, struct sockaddr_ll * sockaddr);
void sockaddrout (struct sockaddr_ll * sockaddr, FILE *fp);

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif
 

