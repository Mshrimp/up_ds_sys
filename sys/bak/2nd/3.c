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
	umask(0);
	/*fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG);*/
	fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		return -1;
	}
	return 0;
}
