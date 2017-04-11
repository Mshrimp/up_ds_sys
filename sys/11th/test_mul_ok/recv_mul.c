/***************************************************
	多播：——接收方
		recv.c文件
		接收多播数据
	实现步骤：
		1、创建套接字，以IP协议发送	----IPPROTO_UDP
			socket();
		2、设置多播为端口重用，使用IP协议
			setsockopt();	----SO_REUSEADDR
		3、设置多播组号，并将IP添加到多播组号中	----IPPROTO_IP
			struct ip_mreq mreq
				mreq.imr_multiaddr.s_addr
				mreq.imr_address.s_addr
				mreq.imr_ifindex
			setsockopt();	----IP_ADD_MEMBERSHIP
		4、设置IP和端口
			struct sockaddr_in
				sin_family
				sin_port
				sin_addr
		5、绑定本机服务器IP和端口
			bind();
		6、接收数据
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


#define PORT 8899
#define MULTICASTIP "225.11.22.33"

//mul recv
int main(int argc, char *argv[])
{
	int sd;
	int ret;
	char buf[128];

	//创建套接字，以数据报格式传输，IP协议
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

	//添加IP到多播组号中
	struct ip_mreqn mreq;
	//多播组号
	mreq.imr_multiaddr.s_addr = inet_addr(MULTICASTIP);		//IP必须是广播地址：224.0.0.0 ~ 239.255.255.255
	mreq.imr_address.s_addr = inet_addr(argv[1]);
	mreq.imr_ifindex = 0;

	ret = setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
	if (ret < 0)
	{
		perror("setsockopt()");
		return -1;
	}

	//设置IP和端口
	struct sockaddr_in src, from;

	src.sin_family = AF_INET;
	src.sin_port = htons(PORT);
	src.sin_addr.s_addr = INADDR_ANY;

	//绑定本机服务器IP端口
	ret = bind(sd, (struct sockaddr *)&src, sizeof(src));
	if (ret < 0)
	{
		perror("bind()");
		close(sd);
		return -1;
	}

	int len = sizeof(from);

	while (1)
	{
		//接收数据
		memset(buf, 0, sizeof(buf));
		ret = recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&from, &len);
		if (ret < 0)
		{
			perror("recvfrom()");
			close(sd);
			return -1;
		}
		printf("%s", buf);
		fflush(NULL);
	}

	close(sd);

	return 0;
}
