/*====================================================================*
 *
 *   pthread-multi.c - create multiple threads;
 *
 *
 *--------------------------------------------------------------------*/

#include <pthread.h>
#include <stdio.h>

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#define PTHREADS 9

/*====================================================================*
 *
 *   void *function(unsigned *pthread);
 *
 *--------------------------------------------------------------------*/

void function (unsigned *pthread) 

{
	printf ("Hello World %d!\n", *pthread);
	pthread_exit ((void *)(0));
}


/*====================================================================*
 *
 *   int main (int argc, char *argv[]);
 *
 *--------------------------------------------------------------------*/

int main (int argc, char *argv []) 

{
	pthread_t pthreads [PTHREADS];
	unsigned pthread;
	signed result;
	for (pthread = 0; pthread < PTHREADS; pthread++) 
	{
		printf ("create thread %d\n", pthread);
		result = pthread_create (&pthreads [pthread], (void *)(0), (void *)(&function), (void *)(&pthread));
		if (result != 0) 
		{
			printf ("ERROR; return code from thread_create() is %d\n", result);
			exit (-1);
		}
	}
	pthread_exit ((void *)(0));
}

