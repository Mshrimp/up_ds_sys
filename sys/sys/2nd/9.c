#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	//0
	char buf[128];
	int flag;

	memset(buf, 0, sizeof(buf));

	flag = fcntl(0, F_GETFL);
	printf("flag = %o\n", flag);

	flag |= O_NONBLOCK;
	fcntl(0, F_SETFL, flag);
	sleep(5);

	read(0, buf, sizeof(buf));

	printf("buf = %s\n", buf);
	return 0;
}
