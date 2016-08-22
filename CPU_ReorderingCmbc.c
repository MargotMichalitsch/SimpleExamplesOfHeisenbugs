/*
 * There are memory barriers, to ensure that there is no compiler reordering.
 * Each loop iteration is protected with semaphores.
 */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

static sem_t sem1;
static sem_t sem2;
static sem_t sem3;

static int x = 0;
static int y = 0;
static int r1 = 0;
static int r2 = 0;

void *funcP1(void *a) {
	for (int i = 0; i < 1000000; i++) {
		sem_wait(&sem1);
		
		x = 1;
		//asm volatile("" ::: "memory");
		r1 = y;

		sem_post(&sem2);
	}
}

void *funcP2(void *a) {
	for (int i = 0; i < 1000000; i++) {
		sem_wait(&sem1);
		
		y = 1;
		//asm volatile("" ::: "memory");
		r2 = x;

		sem_post(&sem2);
	}
}

int main(int argc, char**argv) {

	sem_init(&sem1, 0, 0);
	sem_init(&sem2, 0, 0);

	pthread_t p1, p2;
	pthread_create(&p1, NULL, funcP1, NULL);
	pthread_create(&p2, NULL, funcP2, NULL);

	int reordered = 0;
	for (int i = 0; i < 1000000; i++) {
		sem_post(&sem1);
		sem_post(&sem1);
		sem_wait(&sem2);
		sem_wait(&sem2);

		if (r1 == 0 && r2 == 0) {
			reordered++;
		}
		x = 0;
		y = 0;
	}

	(void) printf("The CPU reordered the statements %d out of 1000000 times.\n", reordered);

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	sem_destroy(&sem1);
	sem_destroy(&sem2);

	return EXIT_SUCCESS;
}
