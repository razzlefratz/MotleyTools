/*====================================================================*
 *
 *   broadcast.h -
 *
 *.  Motley Tools by Charles Maier
 *:  Compiled on Debian GNU/Linux using gcc 2.95 compiler;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef BROADCAST_HEADER
#define BROADCAST_HEADER

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../tools/types.h"

/*====================================================================*
 *   constant declarations;
 *--------------------------------------------------------------------*/

#define BROADCAST_B_BULLET (1 << 0)
#define BROADCAST_B_BANNER (1 << 1)
#define BROADCAST_B_REMOTE (1 << 2)
#define BROADCAST_B_REPORT (1 << 3)
#define BROADCAST_B_STATUS (1 << 4)

#define BROADCAST_T_TIMEOUT 2
#define BROADCAST_L_BANNER 1024
#define BROADCAST_L_BUFFER 1024
#define BROADCAST_MAXCHARS 1600
#define BROADCAST_MAXLINES 20

/*====================================================================*
 *   function declarations;
 *--------------------------------------------------------------------*/

int broadcast (char const *message, flag_t flags);

/*====================================================================*
 *   end declarations;
 *--------------------------------------------------------------------*/

#endif

