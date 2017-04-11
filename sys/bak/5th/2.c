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
	//创建一个孤儿进程
	if (fork() == 0)
	{
		//sleep(1);
		printf("child!\n");
		while(1)
		{
			sleep(1);
		}
	}
	else
	{
		//wait(NULL);
		//sleep(1);
		sleep(10);
		printf("parent!\n");
	}
	return 0;
}
