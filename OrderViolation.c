/*
 * This program has an order violation. If the commented
 * instructions are uncommented, the bug occurs less often.
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

static int x;

void *funcP1(void *a) {
	//(void) printf("Thread 1 started.\n");
	//(void) printf("Value of x: %i\n", x);
        x = 1;
	//(void) printf("Value of x: %i\n", x);
	while (x);
}

void *funcP2(void *a) {
        x = 0;
}

int main(int argc, char**argv) {

	pthread_t p1, p2;
	pthread_create(&p1, NULL, funcP1, NULL);
	//(void) printf("Debugging\n");
	pthread_create(&p2, NULL, funcP2, NULL);

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	return EXIT_SUCCESS;	
}
