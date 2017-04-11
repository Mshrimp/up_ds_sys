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

int main(int argc, char *argv[])
{
	DIR *dir = NULL;
	struct dirent *dp = NULL;

	dir = opendir(argv[1]);
	if (dir == NULL)
	{
		perror("opendir");
		return -1;
	}

	printf("opendir success!\n");

	while(1)
	{
		dp = readdir(dir);
		if (dp == NULL)
		{
			return -1;
		}

		if (dp->d_name[0] == '.')
			continue;

		printf("d_ino = %d\n", dp->d_ino);
		printf("d_off = %d\n", dp->d_off);
		printf("d_reclen = %d\n", dp->d_reclen);
		printf("d_type = %d\n", dp->d_type);
		printf("d_name = %s\n", dp->d_name);
		printf("=================\n");
		
	}

	return 0;
}
