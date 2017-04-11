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

int main(int argc, char *argv[])
{
	int ret;

	printf("hello!\n");

	ret = fork();


	if (ret == 0)
	{
		/*fork();*/
		printf("child!\n");
		printf("work_dir = %s\n", getcwd(NULL, 0));
		/*printf("count = %d\n", count);*/
		printf("*p = %d\n", *p);
	}
	else
	{
		printf("parent!\n");
		printf("work_dir = %s\n", getcwd(NULL, 0));
		int count = 1000;
		int *p = NULL;
		p = (int *)malloc(sizeof(int));
		*p = 1122;
		printf("*p = %d\n", *p);
		printf("count = %d\n", count);
	}
	return 0;
}
