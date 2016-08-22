/*
 * Memory barriers were inserted to prevent CPU and compiler reordering.
 * Loop iterations are protected with semaphores. The program fails sometimes
 * and sometimes not. Adding the printf statement, the race condition occurs
 * extremly rare.
 */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <assert.h>

static sem_t sem1;
static sem_t sem2;

static int x = 0;

void *funcP1(void *a) {
	int help = 0;
	for (int i = 0; i < 10; i++) {
		sem_wait(&sem1);
		
		help = x;
		asm volatile("" ::: "memory");
		asm volatile("mfence" ::: "memory");
		help++;
		asm volatile("" ::: "memory");
		asm volatile("mfence" ::: "memory");
		x = help;

		sem_post(&sem2);
	}
}

void *funcP2(void *a) {
	int help = 0;
	for (int i = 0; i < 10; i++) {
		sem_wait(&sem1);

		//(void) printf("Value of x: %d\n", x);
		help = x;
		asm volatile("" ::: "memory");
		asm volatile("mfence" ::: "memory");
		help++;
		asm volatile("" ::: "memory");
		asm volatile("mfence" ::: "memory");
		x = help;

		sem_post(&sem2);
	}
}

int main(int argc, char**argv) {

	sem_init(&sem1, 0, 0);
	sem_init(&sem2, 0, 0);

	pthread_t p1, p2;
	pthread_create(&p1, NULL, funcP1, NULL);
	pthread_create(&p2, NULL, funcP2, NULL);

	for(int i = 0; i < 10; i++) {
		sem_post(&sem1);
		sem_post(&sem1);
		sem_wait(&sem2);
		sem_wait(&sem2);

	        assert(x == 2);
		x = 0;
	}

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	sem_destroy(&sem1);
	sem_destroy(&sem2);

	return EXIT_SUCCESS;
}
