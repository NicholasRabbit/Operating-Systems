#include <stdio.h>


int main(int argc, char *argv[]) 
{
	long x = 0xdeadbeef;
	int *xp = (int *)x;
	*xp = 12345;		// This line causes a "Segmentation fault". Why ? 
	printf("Done!\n");

	return 0;
}
