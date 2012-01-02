#include <stdio.h>
#include <ulib.h>

int
main(void) {
	forkRT(4,10);
	forkRT(1,8);
	double x = 0;
	double y = 0;
	double z;
	int limit = 1000;
	for (x = 0; x < limit; x++)
		for (y = 0; y < limit; y++) {
			z = 1;
			z /= x+y+1;
		}
	cprintf("exiting pid %d\n", getpid());
    return 0;
}

