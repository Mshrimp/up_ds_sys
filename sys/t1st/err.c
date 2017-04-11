/***************************************************

***************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/*extern errno;*/

int main(int argc, char *argv[])
{
	int fd = 0;
	
	fd = open("./test", O_RDONLY);
	if (-1 == fd)
	{
		printf("errno = %d\n", errno);
		perror("Open");
		return -1;
	}

	return 0;
}
