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
	char buf[128];
	char *p = NULL;

	printf("dir = %s\n", get_current_dir_name());
	/*p = getcwd(NULL, 0);*/
	getcwd(p, 128);
	printf("p = %s %p\n", p, p);
	free(p);

	getchar();
	printf("getcwd = %s\n", getcwd(NULL, 0));
	getcwd(buf, sizeof(buf));

	printf("buf = %s\n", buf);
	chdir("/tmp");
	p = getcwd(buf, sizeof(buf));
	printf("p = %p buf = %p\n", p, buf);

	printf("buf = %s\n", buf);
	fd = creat(argv[1], 0666);
	if (fd == -1)
	{
		return -1;
	}


	return 0;
}
