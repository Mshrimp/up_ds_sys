#include <stdio.h>

int main(void)
{
	char name[128];
	int a = 123;
	snprintf(name , 128, "stu_%d%f", a, 2.33);

	printf("name = %s\n",name);
	return 0;
}
