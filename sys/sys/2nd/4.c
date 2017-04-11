#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd, ret;
	char buf[128];

	/*fd = creat(argv[1], 0666);*/
	/*fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);*/
	/*fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);*/
	fd = open(argv[1], O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		return -1;
	}

	printf("O_WRONLY = %o\n", O_WRONLY);
	printf("o_RDWR = %o\n", O_RDWR);
	printf("O_CREAT = %o\n", O_CREAT);
	printf("O_TRUNC = %o\n", O_TRUNC);
	write(fd, "hello", 5);

	printf("lseek = %d\n", lseek(fd, 0, SEEK_CUR));

	lseek(fd, 0, SEEK_SET);

	printf("lseek = %d\n", lseek(fd, 0, SEEK_CUR));

	ret = read(fd, buf, sizeof(buf));
	printf("ret = %d, buf = %s\n", ret, buf);
	while(1)
	{
		sleep(1);
	}
	return 0;
}
