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

#define PORT1 12345
#define PORT2 54321


//lisi
//lisi -> recv -> port1
// lisi -> send -> port2
int main(int argc, char *argv[])
{
	int sd;
	char buf[128];
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0)
	{
		return -1;
	}

	//lisi -> bind -> port1
	struct sockaddr_in src, from;
	src.sin_family = AF_INET;
	src.sin_port = htons(PORT1);
	src.sin_addr.s_addr = INADDR_ANY;

	bind(sd, (struct sockaddr *)&src, sizeof(src));
	/*sendto(sd, "hello lisi", 11, 0, (struct sockaddr *)&to, sizeof(to));*/
	int len = sizeof(from);
	recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&from, &len);
	printf("lisi : %s\n", buf);

	struct sockaddr_in to;
	to.sin_family = AF_INET;
	to.sin_port = htons(PORT2);
	to.sin_addr.s_addr = inet_addr(argv[1]);

	sendto(sd, "hello zhangsan", 15, 0, (struct sockaddr *)&to, sizeof(to));

	return 0;
}











