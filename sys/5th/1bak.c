/************************************************
	fork()
	创建子进程，子进程拥有父进程一切资源的一份拷贝
	在子进程中修改变量值，不会影响父进程运行结果

************************************************/

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
	
	if(fork() == 0)
	{
		printf("child:\n");
		printf("pid = %d\n", getpid());
		printf("ppid = %d\n", getppid());
		printf("pgrp = %d\n", getpgrp());
		printf("sid = %d\n", getsid(getpid()));
	}
	else
	{
		printf("parent:\n");
		printf("pid = %d\n", getpid());
		printf("ppid = %d\n", getppid());
		printf("pgrp = %d\n", getpgrp());
		printf("sid = %d\n", getsid(getpid()));
	
	}
	return 0;
}







