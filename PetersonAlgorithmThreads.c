/*
 * An implementation of Peterson's algorithm with threads.
 * It works on an Intel core but not on ARM.
 */

#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

static int flag[2];
static int turn;
static int criticalSection = 0;

void *petersonP1(void *a) {
	unsigned int i = 0;
	for (i; i < 400000; i++) {
		flag[0] = 1;
		turn = 1;
		while (flag[1] && (turn == 1));
		criticalSection++;
		assert(criticalSection == 1);
		criticalSection--;
		flag[0] = 0;
	}
}

void *petersonP2(void *a) {
	unsigned int i = 0;
	for (i; i < 400000; i++) {
		flag[1] = 1;
		turn = 0;
		while (flag[0] && (turn == 0));
		criticalSection++;
		assert(criticalSection == 1);
		criticalSection--;
		flag[1] = 0;
	}
}

int main(int argc, char**argv) {

	pthread_t p1, p2;
	pthread_create(&p1, NULL, petersonP1, NULL);
	pthread_create(&p2, NULL, petersonP2, NULL);	
	
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	return EXIT_SUCCESS;
}
