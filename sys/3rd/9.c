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

	printf("login = %s\n", getlogin());

	gethostname(buf, sizeof(buf));
	sethostname("www.hao123.com", 14);
	gethostname(buf, sizeof(buf));

	printf("buf = %s\n", buf);
	return 0;
}
