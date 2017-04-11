#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void hello(int a)
{
	printf("hello 1!\n");
}
void hello(int a, int b)
{
	printf("hello 2!\n");
}

int main(void)
{
	hello(1);
	hello(1, 2);
	return 0;
}
