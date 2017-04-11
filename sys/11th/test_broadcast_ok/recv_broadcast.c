/***************************************************
	广播：——接收方
		recv.c文件
		接收广播数据文件
	实现步骤：
		1、创建套接字，以数据报格式传输，UDP协议
			socket();
		2、设置广播为端口重用
			setsockopt();	----SO_REUSEADDR
		3、设置IP和端口
			struct sockaddr_in
				sin_family
				sin_port
				sin_addr
		4、绑定本机服务器IP端口
			bind();
		5、接收数据
			recvfrom();
			实时打印，需要刷新缓冲区
				fflush(NULL);
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
#include <sys/utsname.h>
#include <dirent.h>
#include <glob.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/resource.h>
#include <pthread.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define PORT 8009

//broadcast recv UDP
int main(int argc, char *argv[])
{
	int sd;
	int ret;
	char ch;
	char buf[128];

	//创建套接字	数据报传输，UDP协议
	sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sd < 0)
	{
		perror("socket()");
		return -1;
	}

	//设置广播为端口重用
	int val = 1;
	ret = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	if (ret < 0)
	{
		perror("setsockopt()");
		return -1;
	}

	//设置IP和端口
	struct sockaddr_in src, from;

	src.sin_family = AF_INET;
	src.sin_port = htons(PORT);
	src.sin_addr.s_addr = INADDR_ANY;	//可接收任意IP发送的数据

	//帮定本机服务器(recv)端口
	ret = bind(sd, (struct sockaddr *)&src, sizeof(src));
	if (ret < 0)
	{
		perror("bind()");
		return -1;
	}

	int len = sizeof(from);

	while (1)
	{
		//接收数据
		memset(buf, 0, sizeof(buf));
		ret = recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&from, &len);
		/*ret = recvfrom(sd, &ch, sizeof(char), 0, (struct sockaddr *)&from, &len);*/
		if (ret < 0)
		{
			perror("recvfrom()");
			close(sd);
			return -1;
		}

		printf("%s", buf);
		/*printf("%c", ch);*/
		//刷新缓冲区，显示信息
		fflush(NULL);
	}

	//关闭套接字
	clsoe(sd);

	return 0;
}
