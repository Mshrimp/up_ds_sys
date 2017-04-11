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

int e = 1122;

int main(int argc, char *argv[])
{
	int ret;
	int count = 10000;

	ret = fork();

	if (ret == -1)
	{
		return -1;
	}
	else if (ret == 0)
	{
		sleep(1);
		printf("child!\n");
		e = 3344;
		printf("e = %d\n", e);
		/*count = 12345;*/
		printf("count = %d %p\n", count, &count);
		printf("pid = %d ppid = %d\n", getpid(), getppid());
		/*return -1;*/
	}
	else
	{
		printf("===========\n");
		count = 54321;
		printf("parent!\n");
		e = 7788;
		printf("e = %d\n", e);
		printf("count = %d %p\n", count, &count);
		printf("pid = %d ppid = %d\n", getpid(), getppid());
	}


	return 0;
}



