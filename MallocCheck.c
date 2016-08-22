/*
 * At some time there is no more memory and so the try to write 'a' to string
 * causes an segmentation fault.
 */

#include <stdlib.h>

int main(int argc, char**argv) {

	char* string = (char*) malloc(1000*(sizeof (char)));

	for(int i = 2; i < 4000000; i++) {
		string = (char*) realloc(string, i*1000*(sizeof (char)));
		string[0] = 'a';
	}
	return EXIT_SUCCESS;
}
