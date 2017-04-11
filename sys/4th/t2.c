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

int main(int argc, char *argv[])
{
	int ret = 0;
	int fd = 0;
	char buf[128] = "Hello world!";

	fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0755);
	if (-1 == fd)
	{
		printf("parent : open failed!\n");
	}

	ret = fork();

	if (-1 == ret)
	{
		printf("fork failed!\n");
		return -1;
	}
	else if (0 == ret)
	{
		char childbuf[] = "child : Hello world!\n";
		printf("child!\n");
		write(fd, childbuf, sizeof(childbuf));
		usleep(300000);
		write(fd, childbuf, sizeof(childbuf));
		usleep(300000);
		write(fd, childbuf, sizeof(childbuf));
		usleep(300000);
		write(fd, childbuf, sizeof(childbuf));
		usleep(300000);
		write(fd, childbuf, sizeof(childbuf));
	}
	else
	{
		char parentbuf[] = "parent : Hello!\n";
		printf("parent!\n");
		write(fd, parentbuf, sizeof(parentbuf));
		usleep(300000);
		write(fd, parentbuf, sizeof(parentbuf));
		usleep(300000);
		write(fd, parentbuf, sizeof(parentbuf));
		usleep(300000);
		write(fd, parentbuf, sizeof(parentbuf));
		usleep(300000);
		write(fd, parentbuf, sizeof(parentbuf));
	}

	close(fd);	

	return 0;
}
