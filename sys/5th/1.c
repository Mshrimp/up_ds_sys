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
	
	if(fork() == 0)
	{
		printf("child:\n");
		printf("pid = %d\n", getpid());
		printf("ppid = %d\n", getppid());
		printf("pgrp = %d\n", getpgrp());
		printf("sid = %d\n", getsid(getpid()));
	}
	else
	{
		printf("parent:\n");
		printf("pid = %d\n", getpid());
		printf("ppid = %d\n", getppid());
		printf("pgrp = %d\n", getpgrp());
		printf("sid = %d\n", getsid(getpid()));
	
	}
	return 0;
}







