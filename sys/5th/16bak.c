/********************************************************************
	vfork()
	创建子进程，子进程先运行，在调用exec或者exit后，父进程才被调度
	子进程和父进程共享数据空间中的变量，在子进程中修改，父进程也会发生变化
	子进程结束必须使用exit函数，否则会报段错误
********************************************************************/

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
		count = 54321;
		printf("count = %d\n", count);
		/*return 0;*/
		exit(0);
	}
	else
	{
		printf("parent! : pid = %d ppid = %d\n", getpid(), getppid());
		/*count = 1000;*/
		printf("count = %d\n", count);
	}
	return 0;
}
