#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[])
{
	int ret;
	struct winsize win;

	system("clear");
	ret = ioctl(1, TIOCGWINSZ, &win);
	if (ret < 0)
	{
		printf("ioctl failed!\n");
		return -1;
	}

	printf("row = %u\n", win.ws_row);
	printf("col = %u\n", win.ws_col);

	printf("\033[%d;%dHhello", win.ws_row / 2, win.ws_col / 2);
	return 0;
}
