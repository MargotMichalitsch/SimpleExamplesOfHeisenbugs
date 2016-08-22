/*
 * Compiled with -O0 the program works fine, but compiled with -O3 (x+1) > x is 
 * optimized to true and there is an infinite loop.
 */

#include <stdio.h>

int main(int argc, char**argv) {

	int x = 2147483640;

	while ((x+1) > x) {
		(void) printf("%d\n", x);
		x++;
	}
}
