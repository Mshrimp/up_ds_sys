/***************************************************
	网络通讯发送结构体数据，接收端
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
	struct cls_t cls;
	int sd = 0;
	int fd = 0;
	int ret = 0;
	char buf[128];

	//创建套接字，数据流传输
	sd = socket(PF_INET, SOCK_STREAM, 0);
	ERRP(-1 == sd, socket, goto ERR1);

	//设置IP和端口
	struct sockaddr_in src, from;
	src.sin_family = AF_INET;
	src.sin_port = htons(PORT);
	src.sin_addr.s_addr = INADDR_ANY;

	//绑定接收服务器IP端口
	ret = bind(sd, (struct sockaddr *)&src, sizeof(src));
	ERRP(-1 == ret, bind, goto ERR2);

	//监听
	ret = listen(sd, 20);
	ERRP(-1 == ret, listen, goto ERR2);

	socklen_t len = sizeof(from);

	fd = accept(sd, (struct sockaddr *)&from, &len);
	ERRP(-1 == fd, accept, goto ERR2);

	//接收数据
#if 1 
	ret = recv(fd, &cls, sizeof(cls), 0);
	printf("ret = %d\n", ret);
	ERRP(-1 == ret, recv, goto ERR2);
#else
	read(fd, &cls, sizeof(cls));
#endif

	printf("ip : %s | name = %s | age = %d | sex = %c | result = %f\n", inet_ntoa(from.sin_addr), cls.name, cls.age, cls.sex, cls.result);

	close(sd);
	close(fd);

	return 0;
ERR2:
	close(sd);
ERR1:
	return -1;
}
