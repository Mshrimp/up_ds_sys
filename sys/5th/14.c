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

extern char **environ;

int main(int argc, char *argv[], char *env[])
{
	int ret;
	char *ar[] = {"ls", "-l", "-h", "-i", NULL};
	char *pr[] = {"test", "hello", "world", "123", "byebye", NULL};
	char *pe[] = {"a=123", "b=hello", "c=tom", NULL};

	printf("main stat! pid = %d\n", getpid());
	/*ret = execl("/bin/ls", "ls", "-l", "-h", "-i", "/ken/sys", NULL);*/
	/*execlp("ls", "ls", "-l", "-h", "-i", NULL);*/
	/*ret = execle("/bin/ls", "ls", "-l", "-h", "-i", NULL, environ);*/
	/*ret = execv("/bin/ls", ar);*/
	/*ret = execvp("/bin/ls", ar);*/
	/*ret = execve("/bin/ls", ar, env);*/
	
	/*execlp("./test", "./test", NULL);*/
	execve("/ken/sys/5th/test", pr, pe);

	if (ret < 0)
	{
		printf("execl failed!\n");
		return -1;
	}
	/*system("ls -l -h -i -a");*/
	printf("main end!\n");
	return 0;
}
