#define _XOPEN_SOURCE
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

	struct spwd *spd;
	char *tmp = NULL;
	while(1)
	{
		read(fd, buf, sizeof(buf));
		printf("buf = %s\n", buf);
		spd = getspnam("root");
		if (spd == NULL)
		{
			printf("getspnam failed!\n");
			return -1;
		}
		tmp = crypt(buf, spd->sp_pwdp);//md5
		if (tmp == NULL)
		{
			printf("md5 failed!\n");
			return -1;
		}
        /*
		 *printf("tmp = %s\n", tmp);
		 *printf("spd->sp_pwdp = %s\n", spd->sp_pwdp);
         */
		if (!strcmp(tmp, spd->sp_pwdp))
		{
			write(fd, "yes", 4);
			break;
		}
		else
		{
			write(fd, "no", 3);
		}
	}

	time_t t;
	time(&t);
	tmp = ctime(&t);
	printf("tmp = %s\n", tmp);
	write(fd, tmp, strlen(tmp) + 1);

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







