
/*
 * As it was suggested in the guidance of MIT 6.S081, it is 
 * necessary to familiar with pointers in C. The following code was 
 * a copy from it.
 * Exercises about pointer in C.
 * */

#include <stdio.h>
#include <stdlib.h>


void f(void) 
{
	int a[4];
	int *b = malloc(16);
	int *c;
	int i;

	printf("1: a = %p, b = %p, c = %p\n", a, b, c);
	
	c = a;
	for (i = 0; i < 4; i++) 
		a[i] = 100 + i;	

	// When 'c[0] = 200', a[0] will be also "200" since 'c' and 'a' 
	// point to the same place in memory.
	c[0] = 200; 
	printf("2: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
			a[0], a[1], a[2], a[3]);

	/*
	 * If a pointer add an integer, it will implicitly add a multiply of the
	 * integer and the size of the data which is referenced by the pointer.
	 * For instance, for a int pointer "c + 2" equals "c + (2x4)";
	 * */
	c[1] = 300;
	// *(c + 2) equals c[2], because a[2] points the same place as c[2] does
	// so the value of it is modified simultaneously.
	*(c + 2) = 301;  
	// '3[c]' affects as same as '*(c + 3)'.
	3[c] = 302;
	printf("3: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
			a[0], a[1], a[2], a[3]);

	// "c", which is initially stored the first index of the array, 
	// pointed to c[1] after adding 1(x4, size of int).
	c = c + 1; 
	*c = 400;  
	printf("4: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
			a[0], a[1], a[2], a[3]);

	/*
	 * "c" pointed to c[1] after the preceding operation, but it was cast
	 * to a pointer with char type in "(char *)c + 1" and it will add only 
	 * 1 (x1) since the size of char is 1 byte. Then "c" was cast to int again.
	 * Consequently, c points to the second byte of "a[1]" so the assignment 
	 * of "*c = 500" modifies the the last three bytes of "a[1]" and the first
	 * byte of "a[2]". Therefore, their value have been changed.
	 * */
	c = (int *) ((char *)c + 1);
	*c = 500;
	printf("5: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
			a[0], a[1], a[2], a[3]);

	// Eventually, the value of "b" is that the address in "a" adds 4
	// and the value of "c" is the result of "a" and 1.
	b = (int *) a + 1;
	c = (int *) ((char *) a + 1);
	printf("6: a = %p, b = %p, c = %p\n", a, b, c);


}


int main(int ac, char **av) 
{
	f();
	return 0;
}


