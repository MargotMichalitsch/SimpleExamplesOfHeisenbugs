/*
 * This program works on little but not on big endian systems.
 */

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

union test {
	uint32_t number;
	uint8_t numberAsArray[4];
};

int main(int argc, char**argv) {

	union test structure;

        structure.number = 0x12345678;
	assert(structure.numberAsArray[0] == 0x78); 

	return EXIT_SUCCESS;
}
