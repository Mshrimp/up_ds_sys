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
	int fd;

	printf("getcwd = %s\n", getcwd(NULL, 0));
	chdir(argv[1]);
/*
 *    fd = open(argv[1], O_RDONLY);
 *    if (fd == -1)
 *    {
 *        return -1;
 *    }
 *
 *    printf("fd = %d\n", fd);
 *
 *    fchdir(fd);
 */
	printf("getcwd = %s\n", getcwd(NULL, 0));

	chdir("..");
	mkdir("./dir2", 0777);
	return 0;
}
