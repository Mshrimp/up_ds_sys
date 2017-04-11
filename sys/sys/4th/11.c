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

	/*printf("main : pid = %d\n", getpid());*/
	ret = fork();

	if (ret == -1)
	{
		printf("fork failed!\n");
	}
	else if (ret == 0)
	{
		usleep(1);
		printf("child!\n");
		/*printf("child : pid = %d\n", getpid());*/
	}
	else
	{
		/*printf("ret = %d\n", ret);*/
		printf("parent!\n");
		/*printf("parent : pid = %d\n", getpid());*/
	}
	return 0;
}
