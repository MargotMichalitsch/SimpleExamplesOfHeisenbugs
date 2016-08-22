/*
 * Two threads try to lock the two same semaphores,
 * but in difference order. Very often a deadlock occurs
 * and then the assertions fails.
 * Adding the printf, the deadlock occurs less often.
 * 
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

static sem_t sem1;
static sem_t sem2;

static int c = 0;
static int flag1 = 0;
static int flag2 = 0;

void *funcP1(void *a) {
	flag1 = 0;
	sem_wait(&sem1);
	flag1 = 1;
	assert(!flag2);
	sem_wait(&sem2);
	c++;
	flag1 = 0;
	sem_post(&sem1);
	sem_post(&sem2);
}

void *funcP2(void *a) {
	//(void) printf("Debugging.\n");
	flag2 = 0;
	sem_wait(&sem2);
	flag2 = 1;
	assert(!flag2);
	sem_wait(&sem1);
	c++;
	flag2 = 0;
	sem_post(&sem2);
	sem_post(&sem1);
}

int main(int argc, char**argv) {

	sem_init(&sem1, 0, 1);
	sem_init(&sem2, 0, 1);

	pthread_t p1, p2;
	pthread_create(&p1, NULL, funcP1, NULL);
	pthread_create(&p2, NULL, funcP2, NULL);

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	sem_destroy(&sem1);
	sem_destroy(&sem2);

	return EXIT_SUCCESS;
}
