#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <shadow.h>
#include <grp.h>
#include <time.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <glob.h>
#include <sys/wait.h>

int *a = NULL, *b = NULL, *c = NULL;

void free_a(void)
{
	printf("free => a!\n");
	free(a);
}
void free_b(void)
{
	printf("free => b!\n");
	free(b);
}
void free_c(void)
{
	printf("free => c!\n");
	free(c);
}

int main(int argc, char *argv[])
{

	a = (int *)malloc(4);	
	b = (int *)malloc(4);	
	c = (int *)malloc(4);	

	
	atexit(free_a);
	*a = 11; 
	*b = 22;
	atexit(free_c);
	*c = 33;

	atexit(free_b);
	printf("*a = %d\n", *a);
	printf("*b = %d\n", *b);
	printf("*c = %d\n", *c);
	return 0;
}
