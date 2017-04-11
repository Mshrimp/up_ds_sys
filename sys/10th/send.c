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
	struct cls_t cls = {"zhang san", 23, 'M', 666.66};
	int s;

	ERRP((s = socket(PF_INET, SOCK_STREAM, 0)) == -1, socket, goto ERR1);

	struct sockaddr_in to;
	to.sin_family = PF_INET;
	to.sin_port = htons(9999);
	to.sin_addr.s_addr = inet_addr(argv[1]);

	ERRP(connect(s, (struct sockaddr *)&to, sizeof(to)) == -1, connect, goto ERR2);

	int ret;
	ERRP((ret = send(s, &cls, sizeof(cls), 0)) < 0, send, goto ERR2);
	/*write(s, "hello", 6);*/

	printf("ret = %d\n", ret);
	close(s);
	return 0;
ERR2:
	close(s);
ERR1:
	return -1;
	



	return 0;
}







