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


int main(int argc, char *argv[])
{
	int fd = 0;

	/*fd = creat(argv[1], 0666);*/
	fd = creat(argv[1], S_IRWXU | S_IRWXG | S_IRWXO);
	/*fd = open(argv[1], 01101, 0666);*/
	if (-1 == fd)
	{
		perror("fd creat");
		return -1;
	}

	return 0;
}
