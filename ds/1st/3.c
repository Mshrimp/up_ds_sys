#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct cls_t{
	char name[128];
	int age;
};
//132
int main(void)
{
	struct cls_t cls[10];

	printf("cls = %p\n", cls);
	printf("cls + 1  = %p", cls + 1);
	return 0;
}
