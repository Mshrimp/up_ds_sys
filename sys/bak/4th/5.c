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
	glob_t gp;
	int ret;
	int i = 0;

	ret = glob(argv[1], 0, NULL, &gp);
	if (ret != 0)
	{
		return -1;
	}

	while(1)
	{
		if (gp.gl_pathv[i] == NULL)
		{
			break;
		}
		printf("%s ", gp.gl_pathv[i]);
		i++;
	}
	printf("\n");

	return 0;
}
