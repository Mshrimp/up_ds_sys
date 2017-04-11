#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd, newfd;

	write(1, "AAAAAA", 6);

	fd = creat("./test", 0666);

	/*write(fd, "hello", 5);*/
	newfd = dup2(fd, 1025);

	printf("fd = %d newfd = %d\n", fd, newfd);
	fflush(NULL);
	/*write("fd = %d newfd = %d\n", fd, newfd);*/

	/*close(2);*/
	sleep(1);
	/*write(, "hello", 5);*/
	return 0;
}
