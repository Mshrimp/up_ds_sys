/***************************************************
	广播：——发送方
		send.c文件
		将本目录下的一个文件广播发送出去
	实现步骤：
		1、创建套接字，以数据报格式发送，UDP协议
			socket();
		2、设置广播
			setsockopt();	----SO_BROADCAST
		3、设置IP和端口
			struct sockaddr_in
				sin_family
				sin_port
				sin_addr
		4、打开要发送的文件
			open();
		5、读取文件内容，并发送
			read();
			sendto();
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
#define BROADCASTFILEPATH "./passwd"

//broadcast send UDP
int main(int argc, char *argv[])
{
	int sd;
	int fd;
	int ret = 0;
	char ch;
	char buf[128] = {};

	//创建套接字	数据报传输，UDP协议
	sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sd < 0)
	{
		perror("socket()");
		exit(-1);
	}

	int val = 1;

	//设置广播
	ret = setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val));
	if (ret < 0)
	{
		perror("setsockopt()");
		exit(-1);
	}

	//设置IP和端口
	struct sockaddr_in to;

	to.sin_family = AF_INET;
	to.sin_port = htons(PORT);
	to.sin_addr.s_addr = inet_addr("2.2.2.255");	//设置广播的IP

    /*
	 *ret = bind(sd, (struct sockaddr *)&src, sizeof(src));
	 *if (ret < 0)
	 *{
	 *    perror("bind()");
	 *    close(sd);
	 *    exit(-1);
	 *}
     */
	
	int len = sizeof(to);

	//打开要发送的数据文件
	fd = open(BROADCASTFILEPATH, O_RDONLY);
	if (fd < 0)
	{
		perror("open()");
		exit(-1);
	}

	while (1)
	{
		//将文件中的数据按字节读取到ch
		ret = read(fd, &ch, sizeof(char));
		if (ret < 0)
		{
			perror("read()");
			exit(-1);
		}

		//如果文件读取到文件结尾，重新定位到文件开头
		if (ret == 0)
		{
			lseek(fd, 0, SEEK_SET);
			continue;
		}
	
		//发送数据
		ret = sendto(sd, &ch, sizeof(char), 0, (struct sockaddr *)&to, sizeof(to));
		if (ret < 0)
		{
			perror("sendto()");
			exit(-1);
		}

		usleep(10000);
	}

	//关闭套接字，关闭文件描述符
	close(fd);
	close(sd);

	return 0;
}
