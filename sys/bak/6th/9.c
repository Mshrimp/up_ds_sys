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


void func(int sig)
{
	printf("pipe!\n");
}
int main(int argc, char *argv[])
{
	int ret;
	int fd[2];
	char buf[1024];
	int count = 0;

	signal(SIGPIPE, func);

	ret = pipe(fd);
	if (ret < 0)
	{
		return -1;
	}

	if (fork() == 0)
	{
		//fd[1]
		/*sleep(1);*/
		close(fd[0]);
		while(1)
		{
			write(fd[1], buf, sizeof(buf));
			printf("count = %d\n", count++);
		}
		/*write(fd[1], "hello", 5);*/
		exit(0);
	}

	wait(NULL);
	close(fd[0]);
	close(fd[1]);

	while(1)
		;
	return 0;
}
