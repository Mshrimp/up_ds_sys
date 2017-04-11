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

int main(int argc, char *argv[])
{
	int ret;
	struct rlimit r;


	ret = getrlimit(RLIMIT_NOFILE, &r);
	/*ret = getrlimit(RLIMIT_CORE, &r);*/
	/*ret = getrlimit(RLIMIT_CPU, &r);*/
	/*ret = getrlimit(RLIMIT_STACK, &r);*/
	if (ret < 0)
	{
		printf("getrlimit failed!\n");
		return -1;
	}

	printf("r.rlim_cur = %d\n", r.rlim_cur);
	printf("r.rlim_max = %d\n", r.rlim_max);
	r.rlim_cur = 10;
	setrlimit(RLIMIT_NOFILE, &r);

	ret = getrlimit(RLIMIT_NOFILE, &r);
	/*ret = getrlimit(RLIMIT_CORE, &r);*/
	/*ret = getrlimit(RLIMIT_CPU, &r);*/
	/*ret = getrlimit(RLIMIT_STACK, &r);*/
	if (ret < 0)
	{
		printf("getrlimit failed!\n");
		return -1;
	}

	printf("r.rlim_cur = %d\n", r.rlim_cur);
	printf("r.rlim_max = %d\n", r.rlim_max);

	int fd;

	while(1)
	{
		fd = open("./test", O_RDONLY);
		if (fd < 0)
		{
			return -1;
		}
		printf("fd = %d\n", fd);
	}
	return 0;
}
