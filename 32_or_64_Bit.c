/*
 * This program works on 32 bit systems, but not on 64 bit systems,
 * because there is an overflow of c.
 */

#include <stdlib.h>
#include <assert.h>

int main(int argc, char**argv) {

	int c = 2147483640;
	long l = 2147483640;
	
	while ((l+1) > l) {
		c++;
		assert(c > 0);
		l++;
	}
	return EXIT_SUCCESS;
}
