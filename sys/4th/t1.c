/***************************************************

***************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
	int ret = 0;

	/*pit_t pid, ppid;*/

	ret = fork();

	if (-1 == ret)
	{
		printf("fork failed!\n");
		return -1;
	}
	else if (ret == 0)
	{
		sleep(2);
		printf("child!\n");
		printf("ret = %d\n", ret);
		printf("child : pid = %d  ppid = %d\n", getpid(), getppid());
	}
	else
	{
		printf("=========================\n");
		printf("parent!\n");
		printf("ret = %d\n", ret);
		printf("parent : pid = %d  ppid = %d\n", getpid(), getppid());
	}

	return 0;
}
