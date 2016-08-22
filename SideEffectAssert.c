/*
 * When compiling with -DNDEBUG or defining NDEBUG before assert.h is included,
 * assertions are not executed and also the instructions in it. The check if c == 5
 * fails then.
 */

//#define NDEBUG

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char**argv) {

	int c = 0;

	for (int i = 0; i < 5; i++) {
		assert(++c > i);
	}

	if (c == 5) {
		(void) printf("Finished successful.\n");
		return EXIT_SUCCESS;
	} else {
		(void) printf("Execution failed.\n");
		return EXIT_FAILURE;
	}
}
