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

#define PORT 8899

//send udp
int main(int argc, char *argv[])
{
	int sd;
	char buf[128];
	int ret;
	//1 创建套接子
	sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sd < 0)
	{
		perror("socket");
		return -1;
	}

// 设置端口重用
	int val = 1;
	ret = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	if (ret == -1)
	{
		printf("setsockopt failed!\n");
		return -1;
	}

	//添加ip到多播组号中
	struct ip_mreqn mreq;
	//表示多播组号
	mreq.imr_multiaddr.s_addr = inet_addr("225.11.22.33");
	mreq.imr_address.s_addr = inet_addr(argv[1]);
	mreq.imr_ifindex = 0;

	ret = setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
	if (ret < 0)
	{
		printf("add ip failed!\n");
		return -1;
	}

	struct sockaddr_in src, from;
	src.sin_family = AF_INET;
	src.sin_port = htons(PORT);
	src.sin_addr.s_addr = INADDR_ANY;
	
	ret = bind(sd, (struct sockaddr *)&src, sizeof(src));
	if (ret < 0)
	{
		printf("bind failed!\n");
		close(sd);
		return -1;
	}
	int len = sizeof(from);

	

	while(1)
	{
		memset(buf, 0, sizeof(buf));
		ret = recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&from, &len);
		if (ret < 0)
		{
			printf("recvfrom failed!\n");
			close(sd);
			return -1;
		}
		printf("%s", buf);
		fflush(NULL);

		/*printf("ip : %s port : %d message : %s\n", inet_ntoa(from.sin_addr), ntohs(from.sin_port), buf);*/
	}
	close(sd);
	return 0;
}









