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
#include <signal.h>

int main(int argc, char *argv[])
{
	int status = 0;

	if (!fork())
	{
		printf("child!\n");
        /*
		 *kill(getpid(), 9);
		 *kill(getpid(), SIGKILL);
         */
		kill(getpid(), 6);
		abort();
		_exit(19);
		exit(20 + 2);
		/*return 10;*/
	}
	else
	{
		wait(&status);
		printf("parent!\n");
		printf("WIFEXITED(status) = %d\n", WIFEXITED(status));
		printf("WEXITSTATUS(status) = %d\n", WEXITSTATUS(status));
		printf("WIFSIGNALED(status) = %d\n", WIFSIGNALED(status));
		printf("WTERMSIG(status) = %d\n", WTERMSIG(status));
		/*printf("status = %d\n", status);*/
	}

	return 0;
}









