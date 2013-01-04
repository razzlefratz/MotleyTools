/*====================================================================*
 *
 *   thread-detach.c -
 *
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <pthread.h>

/*====================================================================*
 *
 *
 *
 *--------------------------------------------------------------------*/

#define PTHREADS	3

/*====================================================================*
 *
 *   void *BusyWork(void *null)
 *   
 *--------------------------------------------------------------------*/

void *BusyWork (void *null) 

{
	int i;
	double result = 0.0;
	for (i = 0; i < 1000000; i++) 
	{
		result = result + (double) random ();
	}
	printf ("result = %e\n", result);
	pthread_exit ((void *) 0);
}


/*====================================================================*
 *
 *   int main (int argc, char *argv[]);
 *   
 *   
 *--------------------------------------------------------------------*/

int main (int argc, char *argv []) 

{
	pthread_t pthreads [PTHREADS];
	pthread_attr_t attr;
	int rc;
	int pthread;
	int status;

/*
 * Initialize and set thread detached attribute 
 */

	pthread_attr_init (&attr);
	pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);
	for (pthread = 0; pthread < PTHREADS; pthread++) 
	{
		printf ("Creating thread %d\n", pthread);
		rc = pthread_create (&pthreads [pthread], &attr, BusyWork, (void *)(0));
		if (rc) 
		{
			printf ("ERROR; return code from pthread_create() is %d\n", rc);
			exit (-1);
		}
	}
	pthread_attr_destroy (&attr);

/*
 * wait for the other threads 
 */

	for (pthread = 0; pthread < PTHREADS; pthread++) 
	{
		rc = pthread_join (pthreads [pthread], (void **) (&status));
		if (rc) 
		{
			printf ("ERROR; return code from pthread_join() is %d\n", rc);
			exit (-1);
		}
		printf ("Completed join with thread %d status= %d\n", pthread, status);
	}

/*
 * exit without terminating threads; 
 */

	pthread_exit ((void *)(0));
}

