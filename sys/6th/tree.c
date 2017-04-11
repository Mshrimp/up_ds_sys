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

void my_tree(char *name)
{
	DIR *dir = NULL;
	struct dirent *dp = NULL;
	static int lev = 0;
	int i;

	dir = opendir(name);
	if (dir == NULL)
	{
		return ;
	}

	chdir(name);
	while((dp = readdir(dir)) != NULL)
	{
		if (strncmp(dp->d_name, ".", 1) == 0 || strcmp(dp->d_name, "..") == 0)
		{
			continue;
		}

		if (dp->d_type == 4)
		{
			for (i = 0; i < lev; i++)
			{
				printf("    ");
			}
			printf("|-- %s\n", dp->d_name);
			lev++;
			my_tree(dp->d_name);
			lev--;
		}
		else
		{
			for (i = 0; i < lev; i++)
			{
				printf("    ");
			}
			printf("|-- %s\n", dp->d_name);
		}

	}
	chdir("..");
	closedir(dir);
}

int main(int argc, char *argv[])
{
	struct stat s;
	int ret;

	printf("%s\n", argv[1]);
	ret = stat(argv[1], &s);
	if (ret < 0)
	{
		perror("stat");
		return -1;
	}

	if (S_ISDIR(s.st_mode))
	{
		my_tree(argv[1]);
	}
	return 0;
}






