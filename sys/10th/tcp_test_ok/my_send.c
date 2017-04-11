/***************************************************
	网络通讯发送结构体数据，发送端
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


#define ERRP(con, func, ret)	do{										\
									if (con)							\
									{									\
										printf(#func" failed!\n");		\
										ret;							\
									}									\
								}while(0)

#define PORT 8989

struct cls_t
{
	char name[32];
	int age;
	char sex;
	float result;
};


int main(int argc, char *argv[])
{
	struct cls_t cls = {"xiami", 25, 'M', 100};
	int sd = 0;
	int ret = 0;
	char buf[128];
	struct sockaddr_in to;

	sd = socket(PF_INET, SOCK_STREAM, 0);
	ERRP(-1 == sd, socket, goto ERR1);
	printf("socket!\n");

	to.sin_family = AF_INET;
	to.sin_port = htons(PORT);
	to.sin_addr.s_addr = inet_addr(argv[1]);

	printf("connect!\n");

	ret = connect(sd, (struct sockaddr *)&to, sizeof(to));
	ERRP(-1 == ret, connect, goto ERR2);

#if 1
	ret = send(sd, &cls, sizeof(cls), 0);
	ERRP(-1 == ret, send, goto ERR2);
#else
	write(sd, &cls, sizeof(cls));
#endif

	printf("ret = %d\n", ret);

	close(sd);

	return 0;
ERR2:
	close(sd);
ERR1:
	return -1;
}
