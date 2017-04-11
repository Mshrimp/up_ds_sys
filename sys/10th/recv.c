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

#define ERRP(con, func, ret) do{							\
					if (con)								\
					{										\
						fprintf(stderr, #func" failed!\n");	\
						ret;								\
					}										\
				}while(0)

struct cls_t{
	char name[128];
	int age;
	char sex;
	float result;
};
int main(int argc, char *argv[])
{
	struct cls_t cls; 
	int s, fd;

	ERRP((s = socket(PF_INET, SOCK_STREAM, 0)) == -1, socket, goto ERR1);

	struct sockaddr_in src, from;
	src.sin_family = PF_INET;
	src.sin_port = htons(9999);
	src.sin_addr.s_addr = INADDR_ANY;

	ERRP(bind(s, (struct sockaddr *)&src, sizeof(src)) == -1, bind, goto ERR2);

	ERRP(listen(s, 20) == -1, listen, goto ERR2);

    /*
	 *printf("sizeof(sin_family) = %d\n", sizeof(src.sin_family));
	 *printf("sizeof(sin_port) = %d\n", sizeof(src.sin_port));
	 *printf("sizeof(sin_addr.s_addr) = %d\n", sizeof(src.sin_addr.s_addr));
	 *printf("sizeof(sin_zero) = %d\n", sizeof(src.sin_zero));
	 *printf("zero = %s\n", src.sin_zero);
	 *strcpy(src.sin_zero, "hellohello");
	 *printf("zero = %s\n", src.sin_zero);
     */
	/*socklen_t len = sizeof(from);*/
	socklen_t len = 16;//表示空间大小
    /*
	 *printf("len = %d\n", sizeof(from));
	 *printf("sizeof(struct sockaddr) = %d\n", sizeof(struct sockaddr));
	 *printf("sizeof(struct sockaddr_in) = %d\n", sizeof(struct sockaddr_in));
     */
	ERRP((fd = accept(s, (struct sockaddr *)&from, &len)) == -1, accept, goto ERR2);

	printf("ip %s\n", inet_ntoa(from.sin_addr));
	/*printf("fd = %d\n", fd);*/
	/*printf("len = %d\n", len);*/

	/*char buf[128];*/
	read(fd, &cls, sizeof(cls));
	/*printf("buf = %s\n", buf);*/
	/*ERRP(recv(fd, &cls, sizeof(cls), 0) == -1, recv, goto ERR3);*/

	printf("ip : %s name : %s age : %d sex : %c result : %.2f\n", inet_ntoa(from.sin_addr), cls.name, cls.age, cls.sex, cls.result);

	close(fd);
	close(s);
	return 0;

ERR3:
	close(fd);
ERR2:
	close(s);
ERR1:
	return -1;
	



	return 0;
}







