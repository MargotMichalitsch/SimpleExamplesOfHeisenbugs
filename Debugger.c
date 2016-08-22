/*
 * Normally the program fails. Compiling with -DNDEBUG or adding #define NDEBUG
 * the assertion does not fail. 
 */

//#define NDEBUG

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char**argv) {

	int test[5];
	int a = 0;
	
	for (int i = 0; i < 5; i++) {
		a += test[i];
	}

	assert(a == 0);
	return EXIT_SUCCESS;
}
