/*
 * An implementation of Peterson's algorithm with processes.
 * It works on an Intel core, but not on an ARM.
 */

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int shmfdFlag = -1;
static int shmfdTurn = -1;
static int shmfdSection = -1;

static int *flag;
static int *turn;
static int *criticalSection;

void peterson(int i, int j) {
	flag[i] = 1;
	*turn = j;
	while (flag[j] && ((*turn) == j));
	(*criticalSection)++;
	assert((*criticalSection) == 1);
	(*criticalSection)--;
	flag[i] = 0;
}

int main(int argc, char**argv) {

	shmfdFlag = shm_open("/myshmFlag", O_CREAT | O_EXCL | O_RDWR, 0600);
	ftruncate(shmfdFlag, 2*(sizeof (int)));
	flag = (int*) mmap(NULL, 2*(sizeof (int)), PROT_WRITE | PROT_READ, MAP_SHARED, shmfdFlag, 0);

	shmfdTurn = shm_open("/myshmTurn", O_CREAT | O_EXCL | O_RDWR, 0600);
	ftruncate(shmfdTurn, sizeof (int));
	turn = mmap(NULL, sizeof (int), PROT_WRITE | PROT_READ, MAP_SHARED, shmfdTurn, 0);

	shmfdSection = shm_open("/myshmSection", O_CREAT | O_EXCL | O_RDWR, 0600);
	ftruncate(shmfdSection, sizeof (int));
	criticalSection = mmap(NULL, sizeof (int), PROT_WRITE | PROT_READ, MAP_SHARED, shmfdSection, 0);

	pid_t pid;
	switch (pid = fork()) {
	case -1: (void) fprintf(stderr, "Error while trying to fork");
		return EXIT_FAILURE;
		break;
	case 0: flag[0] = 0;
		break;
	default: flag[1] = 0;
		break;
	}

	unsigned int i = 0;
	for (i; i < 400000; i++) {
	        if (pid == 0) {
			peterson(0, 1);
		} else {
			peterson(1, 0);
		}
	}

	int status;
	(void) wait(&status);
	if (!WIFEXITED(status)) {
		(void) fprintf(stderr, "Child process was not finished normally");
	}

	close(shmfdFlag);
	close(shmfdTurn);
	close(shmfdSection);

	munmap(flag, sizeof *flag);
	shm_unlink("/myshmFlag");
	munmap(turn, sizeof *turn);
	shm_unlink("/myshmTurn");
	munmap(criticalSection, sizeof *criticalSection);
	shm_unlink("/myshmSection");
	
	return EXIT_SUCCESS;
}
