#define _GNU_SOURCE
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


int main(int argc, char *argv[])
{
	struct utsname name;
	int ret;

	ret = uname(&name);
	if (ret == -1)
	{
		return -1;
	}

	printf("sysname = %s\n", name.sysname);
	printf("nodename = %s\n", name.nodename);
	printf("release = %s\n", name.release);
	printf("version = %s\n", name.version);
	printf("machine = %s\n", name.machine);
	printf("domainname = %s\n", name.domainname);

	return 0;
}
