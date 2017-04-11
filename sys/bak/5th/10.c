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

int main(int argc, char *argv[])
{
	int status;

	if (fork() == 0)
	{
		exit(1000);
	}
	printf("hello!\n");
	wait(&status);
	if (WIFEXITED(status))
	{
		printf("exit = %d\n", WEXITSTATUS(status));
	}
	return 0;



}
