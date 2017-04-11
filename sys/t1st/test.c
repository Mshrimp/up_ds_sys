/***************************************************

***************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd = 0;

	/*fd = open(argv[1], O_RDONLY);*/
	/*fd = open(argv[1], O_RDONLY | O_TRUNC);*/
	fd = open(argv[1], 010);

	if (-1 == fd)
	{
		perror("read file");
		return -1;
	}
	
	fd = close(fd);
	if (0 != fd)
	{
		perror("close");
		return -1;
	}
	
	return 0;
}
