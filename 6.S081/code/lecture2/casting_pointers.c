#include <stdio.h>

int* integers_to_pointer();
long pointer_to_integers();

int main(int argc, char *argv[]) 
{
	int x[4] = {1, 2, 3, 4};
	int *x_ptr = &x[0];
	long x_address = pointer_to_integers(x_ptr);

	int *p; 
	p = integers_to_pointer(x_address);
	printf("x2_ptr is %p\n", p);

	return 0;
}


// "long" data is also integers, it is a long integer.
long pointer_to_integers(int *x_ptr)
{
	long x_address = (long)x_ptr;  // In x86-64 machines, the length of a pointer is 8 bytes, which is as long as a long data.
	printf("x_address is 0x%016lx\n", x_address);   // To print long, use "%lx" because "%x" is used for int by default.
	return x_address;
}


int* integers_to_pointer(long x_address)
{
	int *x2_ptr = (int *)(x_address + 4);	// It points to x[1] now.
	long x2_value = x2_ptr[1];				// It points to x[1+1] now.
	printf("x2_ptr[1] is %ld\n", x2_value);
	return x2_ptr; 
}

