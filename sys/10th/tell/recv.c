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

#define INPUT 10
#define SHOW  3

//lisi
int main(int argc, char *argv[])
{
	int s, fd;
	int ret;
	char buf[128] = {};

	ERRP((s = socket(PF_INET, SOCK_STREAM, 0)) == -1, socket, goto ERR1);

	struct sockaddr_in src, from;
	src.sin_family = PF_INET;
	src.sin_port = htons(atoi(argv[1]));
	src.sin_addr.s_addr = htonl(INADDR_ANY);

	ERRP(bind(s, (struct sockaddr *)&src, sizeof(src)) == -1, bind, goto ERR2);

	ERRP(listen(s, 20) == -1, listen, goto ERR2);
	socklen_t len = 16;//表示空间大小
	ERRP((fd = accept(s, (struct sockaddr *)&from, &len)) == -1, accept, goto ERR2);

	system("clear");
	if (fork() == 0)
	{
		//read
	//usleep(1000);

		fprintf(stderr, "\033[%d;1HZHANGSAN : ", SHOW);
		while(1)
		{
			ERRP((ret = recv(fd, buf, sizeof(buf), 0)) < 0, recv, goto loop);
			fprintf(stderr, "\033[%d;1HZHANFSAN : \033[K%s\033[u", SHOW, buf);
			if (!strcmp(buf, "exit"))
			{
				break;
			}
		}
	loop:
		exit(0);
	}

	//write
	while(1)
	{
		fprintf(stderr, "\033[%d;1HLISI : \033[K\033[s", INPUT);
		fgets(buf, sizeof(buf), stdin);
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = '\0';
		ERRP((send(fd, buf, strlen(buf) + 1, 0) < 0), send, break);
		if (!strcmp(buf, "exit"))
		{
			break;
		}
	}
	wait(NULL);
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







