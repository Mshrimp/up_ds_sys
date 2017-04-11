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
	//1 创建套接子
	sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sd < 0)
	{
		perror("socket");
		return -1;
	}

	int ret;
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









