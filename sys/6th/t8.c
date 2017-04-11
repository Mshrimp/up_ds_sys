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
	int ret, fd[2];
	char buf[128];

	ret = pipe(fd);
	if (ret < 0)
	{
		return -1;
	}

	if (fork() == 0)
	{
	// write fd[0] fd[1]
	//read
	
		sleep(1);
		printf("child!\n");
	read(fd[0], buf, sizeof(buf));//如果管道中没有数据，则处于阻塞状态
		/*write(fd[1], "child hello!", 12);*/
	printf("parent : %s\n", buf);
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	

	//read fd[0] fd[1];
	//write
	/*wait(NULL);*/
	printf("parent!\n");
	/*memset(buf, 0, sizeof(buf));*/
	/*read(fd[0], buf, sizeof(buf));//如果管道中没有数据，则处于阻塞状态*/
		write(fd[1], "child hello!", 12);
	/*printf("parent : %s\n", buf);*/

	close(fd[0]);
	close(fd[1]);
	return 0;
}
