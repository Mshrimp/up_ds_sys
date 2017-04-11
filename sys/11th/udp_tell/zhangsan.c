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

//zhangsan -> send -> port1
//zhangsan -> recv -> port2
int main(int argc, char *argv[])
{
	int sd;
	char buf[128];
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0)
	{
		return -1;
	}

	// zhangsan -> bind -> port2
	struct sockaddr_in src;
	src.sin_family = AF_INET;
	src.sin_port = htons(PORT2);
	src.sin_addr.s_addr = INADDR_ANY;

	bind(sd, (struct sockaddr *)&src, sizeof(src));

	struct sockaddr_in to, from;
	to.sin_family = AF_INET;
	to.sin_port = htons(PORT1);
	to.sin_addr.s_addr = inet_addr(argv[1]);

	sendto(sd, "hello lisi", 11, 0, (struct sockaddr *)&to, sizeof(to));

	int len = sizeof(from);
	recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&from, &len);
	printf("zhangsan : %s\n", buf);
	return 0;
}











