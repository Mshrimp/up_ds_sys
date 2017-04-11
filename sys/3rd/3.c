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

int main(int argc, char *argv[])
{
	struct spwd *spw = NULL;

	spw = getspnam(argv[1]);
	if (spw == NULL)
	{
		printf("getspnam failed!\n");
		return -1;
	}

	printf("getspnam success!\n");
	printf("passwd = %s\n", spw->sp_pwdp);
	return 0;
}
