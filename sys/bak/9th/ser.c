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

//服务器
int main(int argc, char *argv[])
{
	int sd;
	char buf[1024];

	//1 创建套接子文件，用于进程之间通讯
	sd = socket(PF_INET, SOCK_STREAM, 0);
	if (sd == -1)
	{
		printf("socket failed!\n");
		return -1;
	}
	//2 帮定端口
	struct sockaddr_in src, from;
	int ret;
	src.sin_family = AF_INET;
	src.sin_port = htons(PORT);
	src.sin_addr.s_addr = htonl(INADDR_ANY);
	/*src.sin_addr.s_addr = inet_addr("2.2.2.162");*/

	ret = bind(sd, (struct sockaddr *)&src, sizeof(src));
	if (ret == -1)
	{
		printf("bind failed!\n");
		close(sd);
		return -1;
	}

	//3 监听
	listen(sd, 200);

	//4 接受
	int fd;

	int len = sizeof(from);
	while(1)
	{
		
		fd = accept(sd, (struct sockaddr *)&from, &len);
		if (fd == -1)
		{
			close(sd);
			printf("accept failed!\n");
			return -1;

		}
		memset(buf,0,sizeof(buf));
		/*read(fd, buf, sizeof(buf));*/
		write(fd, "service", 8);
		
		printf("from : ip => %s port => %d message : %s\n", inet_ntoa(from.sin_addr), ntohs(from.sin_port), buf);
	}
	printf("fd = %d\n", fd);
	return 0;
}









