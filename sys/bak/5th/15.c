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

int main(int argc, char *argv[], char *env[])
{
	int i;
	printf("test! : pid = %d\n", getpid());
	for (i = 0; i < argc; i++)
	{
		printf("argv[%d] = %s\n", i, argv[i]);
	}
	printf("==================\n");
	i = 0;
	while(env[i] != NULL)
	{
		printf("env[%d] = %s\n", i, env[i]);
		i++;
	}
	/*return 0;*/
}
