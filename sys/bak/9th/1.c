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

int main(int argc, char *argv[])
{
	int i;
	int a = 0x11223344;

	if (*((char *)&a) == 0x11)
	{
		printf("big!\n");
	}
	else
	{
		printf("little!\n");
	}

	for (i = 0; i < 4; i++)
	{
		printf("%p : %0x\n", (char *)&a + i, *((char *)&a + i));
	}
	return 0;
}
