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

	/*ret = link(argv[1], argv[2]);*/
	ret = symlink(argv[1], argv[2]);
	if (ret < 0)
	{
		return -1;
	}
	return 0;
}
