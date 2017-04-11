/*********************************************************
	复制文件描述符
	dup(fd);
	新文件描述符是当前可用文件描述服中的最小数值
	对复制的文件描述符进行读写操作，都会在一个文件中进行
*********************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	int fd1, fd2, fd3;
	fd1 = creat("./test", 0666);	//创建文件，文件权限为读写
	if (fd1 == -1)
	{
		return -1;
	}

	write(fd1, "hellokkk", 8);
	/*fd2 = creat("./test", 0666);*/
	//cp fd1  fd2;
	fd2 = dup(fd1);
	fd3 = dup(fd1);

	printf("fd1 = %d fd2 = %d ", fd1, fd2);
	printf("fd3 = %d\n",fd3);
	write(fd2, "hellokkk", 8);
	write(fd3, "wrold", 5);

	return 0;
}
