#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	float f = 0;

	float a = 3.987;

	printf("f = %f\n", a);
	/*if (f == 0)*/
	if (f > -0.000001 && f < 0.000001)
		printf("hello!\n");
	return 0;
}
