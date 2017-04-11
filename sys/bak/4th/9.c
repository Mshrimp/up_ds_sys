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

//第一个参数：表示接受外部数据个数
//第二个参数：表示接受用户输入数据
//第三个参数：表示环境变量 父进程
int main(int argc, char *argv[], char *env[])
{
	int i = 0;

	while(argv[i] != NULL)
	{
		printf("%s\n", argv[i]);
		i++;
	}
	printf("================\n");
	i = 0;
	while(env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return 0;
}
