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


int main(int argc, char *argv[])
{
	int ret;
	//daemon(0, 0);

	//1 创建孤儿进程
	if ((ret = fork()))
	{
		exit(0);
	}
	else if (ret == -1)
	{
		printf("fork failed!\n");
		return -1;
	}
	
	sleep(1);

	//2 创建新的会话
	setsid();
	printf("pid = %d\n", getpid());
	printf("ppid = %d\n", getppid());
	printf("pgrp = %d\n", getpgrp());
	printf("sid = %d\n", getsid(getpid()));

	//3 设置当前工作目录为根目录
	chdir("/");
	printf("getcwd = %s\n", getcwd(NULL, 0));

	//4 关闭文件描述符
	int i;

	for (i = 0; i < 1024; i++)
	{
		close(i);
	}

	//5 重设umask值
	umask(0);
	mkdir("./dir2", 0777);
/*
 *    int fd;
 *
 *    fd = open("/test/a.txt", O_RDONLY);
 *    if (fd < 0)
 *    {
 *        perror("open");
 *        return -1;
 *    }
 *    printf("fd = %d\n", fd);
 */

	while(1)
		sleep(1);
	return 0;
}
