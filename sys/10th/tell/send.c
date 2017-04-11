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

#define SHOW 3
#define INPUT 10

//zhangsan
int main(int argc, char *argv[])
{
	char buf[128];
	int fd, ret;

	ERRP((fd = socket(PF_INET, SOCK_STREAM, 0)) == -1, socket, goto ERR1);

	struct sockaddr_in to;
	to.sin_family = PF_INET;
	to.sin_port = htons(atoi(argv[1]));
	to.sin_addr.s_addr = inet_addr(argv[2]);

	ERRP(connect(fd, (struct sockaddr *)&to, sizeof(to)) == -1, connect, goto ERR2);


	system("clear");
	if (fork() == 0)
	{
		//read
		//usleep(1000);
		fprintf(stderr, "\033[%d;1HLISI : ", SHOW);
		while(1)
		{
			ERRP((ret = recv(fd, buf, sizeof(buf), 0)) < 0, recv, goto loop);
			fprintf(stderr, "\033[%d;1HLISI : \033[K%s\033[u", SHOW, buf);
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
		fprintf(stderr, "\033[%d;1HZHANGSAN : \033[K\033[s", INPUT);
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
	return 0;
ERR2:
	close(fd);
ERR1:
	return -1;
	



	return 0;
}







