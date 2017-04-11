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
	int ret;
	int fd;

	umask(0);
	ret = mkdir(argv[1], 0777);
	if (ret < 0)
	{
		return -1;
	}

    /*
	 *fd = creat(argv[1], 0666);
	 *if (fd < 0)
	 *{
	 *    return -1;
	 *}
     */

	return 0;
}
