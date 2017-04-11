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
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/time.h>


int main(int argc, char *argv[])
{
	int ret = 0;
	int count = 10;

	ret = vfork();
	if (-1 == ret)
	{
		printf("vfork failed!\n");
		return -1;
	}
	else if (0 == ret)
	{
		sleep(1);
		count++;
		printf("child : pid = %d ppid = %d count = %d\n", getpid(), getppid(), count);
		_exit(0);
	}
	/*else if (ret > 0)*/
	else
	{
		printf("parent : pid = %d ppid = %d count = %d\n", getpid(), getppid(), count);
	}


	return 0;
}
