#include <stdio.h>
#include <stdint.h>

int main (int argc, char const * argv []) 

{
	unsigned bits;
	for (bits = 0; bits < 66; bits++) 
	{
		uint64_t x = 0;
		x = ~x;
		x <<= bits;
		x = ~x;
		printf ("%2d %016llx\n", bits, x);
	}
	return (0);
}

