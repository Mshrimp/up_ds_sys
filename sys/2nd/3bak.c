/*******************************************************************
	open()打开文件时，若文件不存在，则创建文件，并设定为指定权限
	文件权限：mode & ~umask
	默认：umask = 022
	设定权限掩码：umask(n);  例如：umask(0);
*******************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	int fd;
	umask(0);	//设定文件权限掩码，mode & ~umask

	//open()的第三个参数为权限，使用O_CREAT时需要设定第三个参数，为新创建文件的权限
	//open()出错时返回-1
	/*fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG);*/
	fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		return -1;
	}

	return 0;
}

