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

#define PORT 1146

//客户端
int main(int argc, char *argv[])
{
	int sd;

	//1 创建套接子文件，用于进程之间通讯
	sd = socket(PF_INET, SOCK_STREAM, 0);
	if (sd == -1)
	{
		printf("socket failed!\n");
		return -1;
	}

	printf("sd = %d\n", sd);
    /*
	 *fd = open("./test", O_RDWR);
	 *printf("fd = %d\n", fd);
     */
	//2 客户端向服务器发送一个请求连接SYN包
	struct sockaddr_in dest;
	dest.sin_family = AF_INET;
	dest.sin_port = htons(PORT);
	dest.sin_addr.s_addr = inet_addr(argv[1]);
	
	int ret;
	ret = connect(sd, (struct sockaddr *)&dest, sizeof(dest));
	if (ret == -1)
	{
		close(sd);
		printf("connect failed!\n");
		return -1;
	}

	printf("connect success!\n");
	char buf[128];

	/*write(sd, argv[2], strlen(argv[2]) + 1);*/
	read(sd, buf, sizeof(buf));

	printf("buf = %s\n", buf);
	return 0;
}









