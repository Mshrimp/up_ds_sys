/***************************************************

***************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <time.h>

int main(int argc, char *argv[])
{
	struct tm *t;
	time_t tmp, m;

	tmp = time(&m);

	/*t = gmtime(&m);*/
	t = localtime(&m);

	printf("%d-%d %d:%d\n", t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);

	return 0;
}
