#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd;

	printf("fd_size = %d\n", getdtablesize());
	while(1)
	{
		fd = open("./test", O_RDONLY);
		if (fd == -1)
		{
			return -1;
		}
		printf("fd = %d\n", fd);
	}
	return 0;
}
