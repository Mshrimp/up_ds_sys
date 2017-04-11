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

/*extern char **environ;*/

int main(int argc, char *argv[], char *env[])
{
	int i = 0;

	printf("pid = %d\n", getpid());
	system("ls");
	printf("hello!\n");
	printf("pid = %d\n", getpid());

	while(env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	getchar();
	return 0;
}
