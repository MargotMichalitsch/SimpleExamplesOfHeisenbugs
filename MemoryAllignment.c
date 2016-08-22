/**
 * Through the __attribute__((packed)); there is no padding added to bring the
 * elements to their standard allignment. This program shows that the allignment
 * has to be considered and if not there can be bugs.
 */

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

struct unpacked {
	uint16_t first;
	uint32_t second;
} ;

struct packed {
	uint16_t first;
	uint32_t second;
} __attribute__((packed));

int main(int argc, char**argv) {

	struct unpacked up;
	up.first = 0x1234;
	up.second = 0x56789012;

	struct packed *p;
	p = (struct packed*) &up;
	assert(p->first == 0x1234);
	assert(p->second == 0x56789012);

	return EXIT_SUCCESS;
}
