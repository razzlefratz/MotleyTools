/*====================================================================*
 *
 *   pthread-hello.c - pthreaded hello world program;
 *   
 *   
 *--------------------------------------------------------------------*/

#include <stdio.h>
#include <pthread.h>

/*====================================================================*
 *
 *   void _function (void *message);
 *   
 *   
 *--------------------------------------------------------------------*/

void function (void *message) 

{
	static char *string = " ";
	printf ("%s%s", (char *)(message), string);
	string = "\n";
	pthread_exit (0);
}


/*====================================================================*
 *
 *   int main (int argc, char const *argv[]);
 *   
 *   
 *--------------------------------------------------------------------*/

int main (int argc, char const *argv []) 

{
	pthread_t thread1;
	pthread_t thread2;
	char *message1 = "Hello";
	char *message2 = "World";
	pthread_create (&thread1, (void *)(0), (void *) (&function), (void *) (message1));
	pthread_create (&thread2, (void *)(0), (void *) (&function), (void *) (message2));
	pthread_exit ((void *)(0));
}

