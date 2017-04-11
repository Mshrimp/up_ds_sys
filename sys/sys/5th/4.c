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

int test(void)
{
	exit(20);
	printf("hello!\n");
	return 10;
}
int main(int argc, char *argv[])
{
	printf("test = %d\n", test());
	return 0;
}
