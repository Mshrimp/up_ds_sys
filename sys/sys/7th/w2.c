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

	ret = pipe(fd);
	if (ret < 0)
	{
		printf("pipe faied!\n");
		return -1;
	}
	if (fork() == 0)
	{
		//write fd[1]
		//1 
		//cat /etc/passwd
		close(fd[0]);
		dup2(fd[1], 1);
		execlp("cat", "cat", "/etc/passwd", NULL);
		exit(0);
	}

	wait(NULL);
	//read fd[0]
	//grep root
	// 0 fd[0]
	close(fd[1]);
	dup2(fd[0], 0);
	execlp("grep", "grep", "root", NULL);
	return 0;
}
