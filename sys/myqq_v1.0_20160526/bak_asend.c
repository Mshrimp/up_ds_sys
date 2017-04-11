/***************************************************

***************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <time.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <glob.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <signal.h>

#define PATH_A "./a2b"

#define GETLINES(string, buf)	do{										\
									printf(string);						\
									fgets(buf, sizeof(buf), stdin);		\
									if (buf[strlen(buf) - 1] == '\n')	\
									{									\
										buf[strlen(buf) - 1] = '\0';	\
									}									\
								}while(0)


int main(int argc, char *argv[])
{
	int ret = 0;
	int fd = 0;
	char buf[128] = {};

	ret = fork();
	if (-1 == ret)
	{
		printf("send fork failed!\n");
		exit(0);
	}
	else if (0 == ret)
	{
	
	
	}

	fd = open(PATH_A, O_WRONLY);
	if (-1 == fd)
	{
		printf("file open failed!\n");
		return -1;
	}

	while (1)
	{
		GETLINES("A:", buf);

		ret = write(fd, buf, sizeof(buf));
		if (-1 == ret)
		{
			printf("write failed!\n");
			/*unlink(PATH_A);*/
			return -1;
		}

		if (strcmp(buf, "quit") == 0)
		{
			break;
		}
	}

	/*unlink(PATH_A);*/

	return 0;
}
