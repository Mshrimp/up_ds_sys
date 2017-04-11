/*******************************************************
	有名管道实现两个程序通讯功能
	功能：父进程从标准输入接收数据，并写入到管道文件
			子进程从管道文件读取数据
*******************************************************/

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
#include <time.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <glob.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <signal.h>

//管道文件
#define PATH_A "./A2B"
#define PATH_B "./B2A"

#define GETLINES(string, buf)	do{										\
									printf(string);						\
									fgets(buf, sizeof(buf), stdin);		\
									if (buf[strlen(buf) - 1] == '\n')	\
									{									\
										buf[strlen(buf) - 1] = '\0';	\
									}									\
								}while(0)


int main(int argc, char *argv[])
{
	int ret = 0;
	int fdr = 0, fdw = 0;
	char buf[128] = {};

	system("clear");

	ret = mkfifo(PATH_A, 0666);		//创建管道文件
	ret = mkfifo(PATH_B, 0666);

	fdw = open(PATH_A, O_WRONLY);
	if (-1 == fdw)
	{
		printf("%s open failed!\n", PATH_A);
		unlink(PATH_A);
		unlink(PATH_B);
		return -1;
	}

	fdr = open(PATH_B, O_RDONLY);
	if (-1 == fdr)
	{
		printf("%s open failed!\n", PATH_B);
		unlink(PATH_A);
		unlink(PATH_B);
		close(fdw);
		return -1;
	}

	ret = fork();	//创建子进程
	if (-1 == ret)
	{
		printf("send fork failed!\n");
		exit(0);
	}
	else if (0 == ret)
	{
		while (1)
		{
			ret = read(fdr, buf, sizeof(buf));		//从管道文件中读取数据
			if (-1 == ret)
			{
				printf("read failed!\n");
				unlink(PATH_B);
				return -1;
			}

			printf("\033[10;20HB : \033[K%s\033[u", buf);
			fflush(NULL);

			//接收数据并判断结束条件
			if ((strcmp(buf, "exit") == 0) || (strcmp(buf, "quit") == 0))
			{
				break;
			}
		}

		exit(0);
	}

	while (1)	//输入字符串，并将其写入到管道文件
	{
		memset(buf, 0, sizeof(buf));	//清空缓存

		GETLINES("\033[20;20HA : \033[K\033[s", buf);

		ret = write(fdw, buf, sizeof(buf));		//将数据写入到管道文件
		if (-1 == ret)
		{
			printf("write failed!\n");
			return -1;
		}

		//判断输入数据是否结束
		if ((strcmp(buf, "exit") == 0) || (strcmp(buf, "quit") == 0))
		{
			break;
		}
	}

	wait(NULL);			//等待子进程结束
	close(fdr);			//关闭管道文件
	close(fdw);
	unlink(PATH_A);		//清除管道文件
	unlink(PATH_B);

	return 0;
}
