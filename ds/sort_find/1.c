#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int a = 10;
	int b = 10;

	int c[10] = {10};

	//a[0] a[0]

	printf("a = %d b = %d\n", a, b);
	a ^= b;
	b ^= a;
	a ^= b;
	printf("a = %d b = %d\n", a, b);

	printf("c[0] = %d\n", c[0]);
	c[0] ^= c[0];
	c[0] ^= c[0];
	c[0] ^= c[0];
	printf("c[0] = %d\n", c[0]);
	return 0;
}
