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

#define PORT 1133

int main(int argc, char *argv[])
{
	int sd;
	int ret;
	int i;
	struct sockaddr_in dest;
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr("2.2.2.108");
	// 0 ~ 65535

	//1 创建套接子文件，用于进程之间通讯

	for (i = 0; i < 65536; i++)
	{
		sd = socket(PF_INET, SOCK_STREAM, 0);
		if (sd == -1)
		{
			printf("socket failed!\n");
			return -1;
		}
		dest.sin_port = htons(i);
		ret = connect(sd, (struct sockaddr *)&dest, sizeof(dest));
		if (ret == 0)
		{
			printf("%d ", i);
		}
		close(sd);
	}
	return 0;
}









