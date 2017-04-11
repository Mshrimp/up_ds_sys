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
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	int ret;
	int fd[2];
	char buf[128];

	ret = pipe(fd);
	if (ret < 0)
	{
		printf("pipe failed!\n");
		return -1;
	}

	printf("pipe success!\n");
	
	printf("fd[0] = %d\n", fd[0]);
	printf("fd[1] = %d\n", fd[1]);
	//fd[0] -> read
	//fd[1] -> write

	
	ret = write(fd[1], "hello", 5);
	if (ret < 0)
	{
		printf("write failed!\n");
		return -1;
	}

	printf("ret = %d\n", ret);

	memset(buf, 0, sizeof(buf));
	read(fd[0], buf, 2);
	printf("buf = %s\n", buf);

	memset(buf, 0, sizeof(buf));
	read(fd[0], buf, sizeof(buf));
	printf("buf = %s\n", buf);
	close(fd[0]);
	close(fd[1]);
	return 0;
}
