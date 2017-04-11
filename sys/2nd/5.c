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
	fd1 = creat("./test", 0666);
	if (fd1 == -1)
	{
		return -1;
	}

	/*write(fd1, "hellokkk", 8);*/
	/*fd2 = creat("./test", 0666);*/
	//cp fd1  fd2;
	fd2 = dup(fd1);
	fd3 = dup(fd1);

	printf("fd1 = %d fd2 = %d\n", fd1, fd2);
	printf("fd3 = %d\n",fd3);
	write(fd1, "hellokkk", 8);
	write(fd2, "wrold", 5);

	return 0;
}
