#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int ret, fd;
	char buf[128] = "helloworld";

	/*fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC);*/
	fd = open(argv[1], O_CREAT);
	if (fd == -1)
	{
		return -1;
	}

    /*
	 *ret = write(fd, buf, strlen(buf));
	 *if (ret == -1)
	 *{
	 *    return -1;
	 *}
	 *printf("ret = %d\n", ret);
     */
	ret = read(fd, buf, sizeof(buf));
	if (ret == -1)
	{
		close(fd);
		return -1;
	}

	printf("ret = %d\n", ret);
	printf("buf = %s\n", buf);
	close(fd);
	return 0;
}
