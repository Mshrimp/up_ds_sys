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

	while(1)
	{
		fd = open("./test", O_RDONLY);
		if (fd == -1)
		{
			break;
		}
		printf("fd = %d\n", fd);
	}
	close(1000);
	close(500);

	fd = open("./test", O_RDONLY);
	if (fd == -1)
	{
		return -1;
	}
	printf("last : fd = %d\n", fd);
	return 0;
}
