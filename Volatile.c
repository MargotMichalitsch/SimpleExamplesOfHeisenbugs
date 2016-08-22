/*
 * Most programmers think that using volatile guarantees atomicity, this program
 * shows, that this is not the case.
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>

volatile int x = 0;

static sem_t sem1;

void *threadFunc(void *a) {
        x++;
	sem_post(&sem1);
}

int main(int argc, char**argv) {

	sem_init(&sem1, 0, 0);
	
	pthread_t p1, p2;
	pthread_create(&p1, NULL, threadFunc, NULL);
	pthread_create(&p2, NULL, threadFunc, NULL);

	sem_wait(&sem1);
	sem_wait(&sem1);
	assert(x == 2);

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	sem_destroy(&sem1);

	return EXIT_SUCCESS;
}
