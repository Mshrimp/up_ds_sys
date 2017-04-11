/***************************************************
	多播：——发送方
		send.c文件
		将本目录下一个文件按多播方式发送出去
	实现步骤：
		1、创建套接字，以IP协议发送
			socket();
		2、设置多播，使用IP协议	----IPPROTO_IP
			setsockopt();	----IP_MULTICAST_LOOP
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


#define PORT 8899
#define MULTIPATH "./passwd"
#define MULTICASTIP	"225.11.22.33"


//mul send 
int main(int argc, char *argv[])
{
	int sd;
	int ret;

	//创建套接字，以数据报格式传输
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0)
	{
		perror("socket()");
		return -1;
	}

	//设置多播，使用IP协议
	int val = 1;

	ret = setsockopt(sd, IPPROTO_IP, IP_MULTICAST_LOOP, &val, sizeof(val));
	if (ret < 0)
	{
		perror("setsockopt()");
		return -1;
	}

	//设置IP和端口
	struct sockaddr_in to;

	to.sin_family = AF_INET;
	to.sin_port = htons(PORT);
	to.sin_addr.s_addr = inet_addr(MULTICASTIP);		//必须使用广播IP，224.0.0.0~239.255.255.255

	//打开要发送的数据文件
	int fd;
	char ch;

	fd = open(MULTIPATH, O_RDONLY);
	if (fd < 0)
	{
		perror("open()");
		return -1;
	}

	while (1)
	{
		//按字符逐个读取文件中的数据
		ret = read(fd, &ch, sizeof(char));
		if (ret <= 0)
		{
			lseek(fd, 0, SEEK_SET);	//读取结束或失败，重新定位到文件开头读取
			continue;
		}

		//发送数据
		ret = sendto(sd, &ch, sizeof(char), 0, (struct sockaddr *)&to, sizeof(to));
		if (ret < 0)
		{
			perror("sendto()");
			return -1;
		}

		usleep(10000);
	}

	//关闭套接字，关闭文件描述符
	close(fd);
	close(sd);

	return 0;
}
