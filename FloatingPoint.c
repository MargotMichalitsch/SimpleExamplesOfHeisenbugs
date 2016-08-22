/*
 * On a Intel core the program fails, because the printf statements
 * cause writes of "a" to the main memory and there it is saved
 * with 80 bit. This is only the case with optimization level 3 and 
 * when x87 instructions are used, enabled with -mfpmath=387 while compiling.
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double a = 0;
static double b = 0;

void func1() {
	for (int i = 0; i < 10; i++) {
		a += M_SQRT1_2;
		(void) printf("a: %f\n", a);
		a *= M_E;
		(void) printf("a: %f\n", a);
		a -= 0.195;
		(void) printf("a: %f\n", a);
		a *= M_LOG2E;
		(void) printf("a: %f\n", a);
		a /= M_PI;
		(void) printf("a: %f\n", a);
		a *= M_SQRT2;
		(void) printf("a: %f\n", a);
		a /= M_1_PI;
		(void) printf("a: %f\n", a);
	}
}

void func2() {
	for (int i = 0; i < 10; i++) {
		b += M_SQRT1_2;
		b *= M_E;
		b -= 0.195;
		b *= M_LOG2E;
		b /= M_PI;
		b *= M_SQRT2;
		b /= M_1_PI;
	}
}

int main(int argc, char**argv) {

	func1();
	func2();

	assert(fabs(a-b) < 0.00000000001);

	return EXIT_SUCCESS;
}
