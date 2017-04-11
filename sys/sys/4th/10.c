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
	char *p = NULL;

	p = getenv("HOSTNAME");
	/*p = getenv("SHELL");*/
	if (p == NULL)
	{
		printf("getenv failed!\n");
		return -1;
	}

	printf("p = %s\n", p);

	putenv("HOSTNAME=www.baidu.com");
	/*setenv("HOSTNAME", "www.uplooking.com", 1);*/
	p = getenv("HOSTNAME");
	printf("p = %s\n", p);

	/*unsetenv("HOSTNAME");*/
	clearenv();
	p = getenv("HOSTNAME");
	p = getenv("HOME");
	p = getenv("SHELL");
	printf("p = %s\n", p);

	return 0;
}
