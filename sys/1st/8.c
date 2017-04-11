#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	FILE *fp = NULL;
	int ret;
	int fd;
	char buf[128];

#if 1
	//8192
	fp = fopen("./test", "w");
	if (fp == NULL)
	{
		return -1;
	}
	
	/*setvbuf(fp, buf, _IONBF, 128);*/
	setvbuf(fp, buf, _IOFBF, 5);

	ret = fwrite("hello", 5, 1, fp);
	if (ret != 1)
	{
		perror("write");
		return -1;
	}

#else
	fd = open("./test", O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
	{
		return -1;
	}

	ret = write(fd, "hello", 5);
	if (ret < 0)
	{
		return -1;
	}
#endif
	sleep(10);
	/*close(fd);*/
	/*fclose(fp);*/
	return 0;
}
