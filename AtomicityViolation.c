/*
 * Each thread locks the same semaphore saves the value of the global variable
 * c locally to help and releases the lock. Then increases help, locks again
 * the same semaphore and saves help to c. Two additional semaphores are used
 * to protect one loop iteration against another.
 */

#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>

static sem_t sem1;
static sem_t sem2;
static sem_t sem3;

static int c = 0;

void *funcP1(void *a) {
	int help = 0;
	for (int i = 0; i < 10; i++) {
		sem_wait(&sem2);
		
		sem_wait(&sem1);
		help = c;
		sem_post(&sem1);

		help++;
		
		sem_wait(&sem1);
		c = help;
		sem_post(&sem1);

		sem_post(&sem3);
	}
}

void *funcP2(void *a) {
	int help = 0;
	for (int i = 0; i < 10; i++) {
		sem_wait(&sem2);
		
		sem_wait(&sem1);
		help = c;
		sem_post(&sem1);

		help++;
		
		sem_wait(&sem1);
		c = help;
		sem_post(&sem1);

		sem_post(&sem3);
	}
}

int main(int argc, char**argv) {

	sem_init(&sem1, 0, 1);
	sem_init(&sem2, 0, 0);
	sem_init(&sem3, 0, 0);

	pthread_t p1, p2;
	pthread_create(&p1, NULL, funcP1, NULL);
	pthread_create(&p2, NULL, funcP2, NULL);

	for (int i = 1; i <= 10; i++) {
		sem_post(&sem2);
		sem_post(&sem2);
		sem_wait(&sem3);
		sem_wait(&sem3);

		assert(c == 2*i);
	}

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	sem_destroy(&sem1);
	sem_destroy(&sem2);
	sem_destroy(&sem3);

	return EXIT_SUCCESS;
}
