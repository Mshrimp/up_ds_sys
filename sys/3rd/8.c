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

int main(int argc, char *argv[])
{
	char buf[128];
	int ret;

	printf("file = %s\n", argv[1]);
	ret = readlink(argv[1], buf, sizeof(buf));
	if (ret == -1)
	{
		return -1;
	}

	printf("buf = %s\n", buf);
	printf("%s -> %s\n", argv[1], buf);

	return 0;
}
