#include <stdio.h>
#include <stdlib.h>

/*
 * When a function is completed, the stack will be reset, therefore, the local array is cease to 
 * exist. As a result, returning the address of a local array is dangerous because the memory will
 * replaced by new functions. 
 */
int *multiples_of(int number, int max)
{
	int my_local_array[max];
	int i;
	for (i = 0; i < max; i++)
		my_local_array[i] = number * (i + 1);

	return &my_local_array[0]; // When it is being compiled, the compiler warns: "function returns address of local variable".
}

// Fixed
int *multiples_of_fixed(int number, int max)
{
	int *my_local_array = malloc(sizeof(int) * max);	// Don't forget to "free" the returned pointer.
	int i;
	for (i = 0; i < max; i++)
		my_local_array[i] = number * (i + 1);
	return &my_local_array[0];

}


int main(int argc, char *argv[]) 
{
	multiples_of(10, 8);
	int *ip = multiples_of_fixed(10, 8);
	printf("ip is %p\n", ip);
	free(ip);

	return 0;
}
