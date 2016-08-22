/*
 * Compiled with -O0 there is an infinite loop, compiled with -O1 the assertion
 * fails. The printf is necessary, that y is not optimized away.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

static int x = 0;
static int y = 0;

void *threadFunc(void *a) {
	x = 15;
}

int main(int argc, char**argv) {

	pthread_t p1;

	(void) printf("%i\n", y);
        x = 5;
	pthread_create(&p1, NULL, threadFunc, NULL);
	while (1) {
		y = x;
		assert(y == 5);
	}

	pthread_join(p1, NULL);

	return EXIT_SUCCESS;
}
