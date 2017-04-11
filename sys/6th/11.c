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
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	int ret;
	int fd;
	char buf[128] = {};

	ret = mkfifo("./ken", 0666);
	if (ret < 0)
	{
		printf("mkfifo failed!\n");
		return -1;
	}

	printf("mkfifo success!\n");

	fd = open("./ken", O_RDWR);

	if (fork() == 0)
	{
		//write(fd, "hello", 5);
		read(fd, buf, sizeof(buf));
		printf("buf = %s\n", buf);
		close(fd);
		exit(0);
	}


	write(fd, "parent", 6);
	/*read(fd, buf, sizeof(buf));*/
	wait(NULL);

	close(fd);
	unlink("./ken");
	return 0;
}
