/*
 * This program uses TSC (time stamp counter) for a timer. There are 4 threads
 * and all check if the value of TSC is higher than the last value of it. To lock
 * the global variable timer, a spinlock is used.
 */

#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

static pthread_mutex_t mutex1;
static pthread_mutex_t mutex2;
static pthread_mutex_t mutex3;
static pthread_mutex_t mutex4;
static pthread_mutex_t mutex5;
static pthread_mutex_t mutex6;
static pthread_mutex_t mutex7;
static pthread_mutex_t mutex8;

static volatile uint64_t timer = 0;
static volatile uint32_t spinlock = 1;

static void spin_wait(volatile uint32_t *lock) {
  asm volatile(
    "movl $0, %%ebx;\n"
    "1: xchg %%ebx, %0;\n"
    "cmp $0, %%ebx;\n"
    "je 1b;\n"
    :
    : "m"(lock)
    : "ebx"
    );
}

static void spin_post(volatile uint32_t *lock) {
  asm volatile(
    "mov $1, %%ebx;\n"
    "xchg %%ebx, %0;\n"
    :
    : "m"(lock)
    : "ebx"
    );
}

static inline uint64_t rdtsc() {
	uint64_t time = 0;
	asm volatile("rdtsc" : "=A"(time));
	return time;
}

void *funcP1(void *a) {
	uint64_t t = 0;
	for (int i = 0; i < 10000; i++) {
	        pthread_mutex_lock(&mutex1);
		spin_wait(&spinlock);
		t = rdtsc();
		assert(t >= timer);
		timer = t;
	        spin_post(&spinlock);
	        pthread_mutex_unlock(&mutex5);
	}
}

void *funcP2(void *a) {
	uint64_t t = 0;
	for (int i = 0; i < 10000; i++) {
		pthread_mutex_lock(&mutex2);
	        spin_wait(&spinlock);
		t = rdtsc();
		assert(t >= timer);
		timer = t;
	        spin_post(&spinlock);
		pthread_mutex_unlock(&mutex6);
	}
}

void *funcP3(void *a) {
	uint64_t t = 0;
	for (int i = 0; i < 10000; i++) {
	        pthread_mutex_lock(&mutex3);
	        spin_wait(&spinlock);
		t = rdtsc();
		assert(t >= timer);
		timer = t;
	        spin_post(&spinlock);
		pthread_mutex_unlock(&mutex7);
	}
}

void *funcP4(void *a) {
	uint64_t t = 0;
	for (int i = 0; i < 10000; i++) {
	        pthread_mutex_lock(&mutex4);
	        spin_wait(&spinlock);
		t = rdtsc();
		assert(t >= timer);
		timer = t;
	        spin_post(&spinlock);
		pthread_mutex_unlock(&mutex8);
	}
	}

int main(int argc, char**argv) {

	pthread_t p1, p2, p3, p4;
	pthread_create(&p1, NULL, funcP1, NULL);
	pthread_create(&p2, NULL, funcP2, NULL);
	pthread_create(&p3, NULL, funcP3, NULL);
	pthread_create(&p4, NULL, funcP4, NULL);

        pthread_mutex_init(&mutex1,NULL);
	pthread_mutex_init(&mutex2,NULL);
	pthread_mutex_init(&mutex3,NULL);
	pthread_mutex_init(&mutex4,NULL);
	pthread_mutex_init(&mutex5,NULL);
	pthread_mutex_init(&mutex6,NULL);
	pthread_mutex_init(&mutex7,NULL);
	pthread_mutex_init(&mutex8,NULL);

	for (int i = 0; i < 10000; i++) {
	        pthread_mutex_lock(&mutex5);
		pthread_mutex_lock(&mutex6);
		pthread_mutex_lock(&mutex7);
		pthread_mutex_lock(&mutex8);
		pthread_mutex_unlock(&mutex1);
		pthread_mutex_unlock(&mutex2);
		pthread_mutex_unlock(&mutex3);
		pthread_mutex_unlock(&mutex4);
	}
	
        pthread_mutex_destroy(&mutex1);
	pthread_mutex_destroy(&mutex2);
	pthread_mutex_destroy(&mutex3);
	pthread_mutex_destroy(&mutex4);
	pthread_mutex_destroy(&mutex5);
	pthread_mutex_destroy(&mutex6);
	pthread_mutex_destroy(&mutex7);
	pthread_mutex_destroy(&mutex8);

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);
	pthread_join(p4, NULL);

	return EXIT_SUCCESS;
}
