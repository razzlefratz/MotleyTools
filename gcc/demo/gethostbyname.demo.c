/*====================================================================*
 *
 *   gethostbyname.c - domonstration of gethostbyname() function; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IPADDR(hostent) *(struct in_addr *)(*(hostent)->h_addr_list)

int main (int argc, char const *argv []) 

{
	struct hostent *hostent;
	while (*++argv != (char const *)(0)) 
	{
		if ((hostent = gethostbyname (*argv)) != (struct hostent *)(0)) 
		{
			printf ("[%s]\n", hostent->h_name);
			while (*hostent->h_aliases != (char *)(0)) 
			{
				printf ("  [%s]\n", *hostent->h_aliases++);
			}
			printf ("  [%s]\n", inet_ntoa (IPADDR (hostent)));
		}
	}
	return (0);
}

