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

int main(int argc, char *argv[])
{
	int ret = 0;
	int i = 0;
	int fd = 0;
	char buf[128] = {};
	char temp[128] = {};
	int count = 0;

	ret = fork();	//创建孤儿进程
	if (-1 == ret)
	{
		printf("fork failed!\n");
		return -1;
	}
	else if (ret > 0)
	{
		exit(0);
	}

	setsid();		//创建新会话

	ret = chdir("/");	//切换工作目录
	if (-1 == ret)
	{
		printf("chdir failed!\n");
		return -1;
	}

	for (i = 0; i < 1024; i++)		//关闭文件描述符
	{
		close(i);
	}

	umask(0);

	while(1)
	{
		fd = open("/tmp/log", O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (-1 == ret)
		{
			printf("open file failed!\n");
			return -1;
		}

		strcpy(temp, __TIME__);
		strcat(temp, "  ");
		
		buf[0] = rand() % 26 + 'A';
		for (i = 1; i < 31; i++)
		{
			buf[i] = rand() % 26 + 'a';
		}
		buf[i] = '\n';

		strcat(temp, buf);

		ret = write(fd, temp, sizeof(buf));

		close(fd);
		count++;
		sleep(1);
	}


	return 0;
}
