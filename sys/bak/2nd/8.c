#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd, tmp_fd;
	int flag = 0;

	fd = open("./test", O_WRONLY);
	if (fd == -1)
	{
		return -1;
	}


	flag = fcntl(fd, F_GETFL);
	printf("flag = %o\n", flag);

	flag |= O_APPEND;
	/*flag |= O_TRUNC;*/
	printf("flag = %o\n", flag);
	fcntl(fd, F_SETFL, flag);

	write(fd, "AAA", 3);
	/*tmp_fd = dup(fd);*/
	//dip2()
	//等价于dup dup2
#if 0
	tmp_fd = fcntl(fd, F_DUPFD, 888);
	if (tmp_fd == -1)
	{
		printf("fcntl failed!\n");
		return -1;
	}

	printf("tmp_fd = %d\n", tmp_fd);
	write(fd, "hello", 5);
	write(tmp_fd, "hello", 5);

	close(fd);
	close(tmp_fd);
#endif
	return 0;
}
