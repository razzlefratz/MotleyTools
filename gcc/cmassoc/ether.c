#include <stdio.h>
#include <net/ethernet.h>

int main (int argc, char const * argv []) 

{
	printf ("ETHER_MAX_LEN %d\n", ETHER_MAX_LEN);
	printf ("ETHER_MIN_LEN %d\n", ETHER_MIN_LEN);
	printf ("ETHER_HDR_LEN %d\n", ETHER_HDR_LEN);
	printf ("ETHER_ADDR_LEN %d\n", ETHER_ADDR_LEN);
	printf ("ETHER_TYPE_LEN %d\n", ETHER_TYPE_LEN);
	printf ("ETHER_CRC_LEN %d\n", ETHER_CRC_LEN);
	printf ("ETHERMTU %d\n", ETHERMTU);
	printf ("ETHERMIN %d\n", ETHERMIN);
	return (0);
}

