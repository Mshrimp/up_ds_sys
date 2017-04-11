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
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/select.h>

int main(int argc, char *argv[])
{
	int ret;
	int fd;
	fd_set rfd;

	struct timeval time;
	time.tv_sec = 0;
	time.tv_usec = 0;
	char buf[128];

	//管道文件
	mkfifo("ken", 0666);
	
	fd = open("./ken", O_RDWR);
	if (fd == -1)
	{
		printf("open failed!\n");
	}
	// 0 标准输入


	while(1)
	{
		FD_ZERO(&rfd);//表示清空读集
		FD_SET(fd, &rfd);// 表示管道加入读集
		FD_SET(0, &rfd);//表示标准输入到读集
		ret = select(fd + 1, &rfd, NULL, NULL, &time);
		printf("ret = %d\n", ret);
		if (ret > 0)
		{
			/*printf("select success!\n");*/
			if (FD_ISSET(fd, &rfd))
			{
				memset(buf, 0, sizeof(buf));
				read(fd, buf, sizeof(buf));
				printf("mkfifo : %s\n", buf);
			}
			else
			{
				memset(buf, 0, sizeof(buf));
				read(0, buf, sizeof(buf));
				printf("stdin : %s\n", buf);
			}
			/*break;*/
		}
		else if (ret == 0)
		{
			printf("time out!\n");
			return -1;
		}
		else
		{
			printf("select failed!\n");
			return -1;
		}
	}


	return 0;
}
