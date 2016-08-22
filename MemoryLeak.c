/*
 * The program is killed by the system or terminates with EXIT_FAILURE,
 * when memory is limited with ulimit.
 */

#include <stdlib.h>
#include <stdio.h>

int allocate() {
	char* data = (char*) malloc(9000 * sizeof(char));
	if (data == NULL) {
		(void) printf("Allocating memory failed.\n");
		return -1;
	}
	data = "Memory Leak";
	return 0;
}

int main(int argc, char**argv) {
	
        for (int i = 0; i < 4000000; i++) {
		if (allocate() == -1) {
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}
