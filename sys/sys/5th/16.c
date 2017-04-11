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
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char *argv[])
{
	int ret;
	int count = 12345;

	ret = vfork();
	if (ret == -1)
	{
		printf("vfork failed!\n");
		return -1;
	}
	else if (ret == 0)
	{
		sleep(1);
		printf("child! : pid = %d ppid = %d\n", getpid(), getppid());
		/*count = 54321;*/
		printf("count = %d\n", count);
		/*return 0;*/
		exit(0);
	}
	else
	{
		printf("parent! : pid = %d ppid = %d\n", getpid(), getppid());
		count = 1000;
		printf("count = %d\n", count);
	}
	return 0;
}
