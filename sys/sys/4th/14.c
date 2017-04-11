#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <shadow.h>
#include <grp.h>
#include <time.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <glob.h>

int main(int argc, char *argv[])
{
	int fd;
	int count = 1000;
	int i, j;
	char buf[128];

	fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
	{
		return -1;
	}

	if (fork() == 0)
	{
		for (i = 0; i < 1000; i++)
		{
			snprintf(buf, sizeof(buf), "child : count = %d\n", i);
			for (j = 0; j < strlen(buf); j++)
			{
				write(fd, &buf[j], 1);
			}
		}
		close(fd);
	}
	else
	{
		/*printf("parent!\n");*/
		wait(NULL);
		for (i = 0; i < 1000; i++)
		{
			snprintf(buf, sizeof(buf), "parent : count = %d\n", i);
			for (j = 0; j < strlen(buf); j++)
			{
				write(fd, &buf[j], 1);
			}
			/*write(fd, buf, strlen(buf));*/
		}
		/*write(fd, "parent", 6);*/
		close(fd);
	}
	return 0;
}
