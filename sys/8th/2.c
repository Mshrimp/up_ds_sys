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

void *hello(void *data)
{
	int i, count = 1000 ;
	printf("hello : pthread_self = %u\n", pthread_self());
	printf("hello : pid = %d\n", getpid());
	printf("hello!\n");

	for (i = 0; i < 10; i++)
	{
		/*sleep(1);*/
		if (fork() == 0)
		{
			count++;
			printf("child! : pid = %d pth = %u count = %d\n", getpid(), pthread_self(), count);
			exit(0);
		}
	}
    /*
	 *for (i = 0; i < 10; i++)
	 *    wait(NULL);
     */

		printf("parent! : pid = %d pth = %u\n", getpid(), pthread_self());
}
int main(int argc, char *argv[])
{
	int ret;
	pthread_t pth;

	ret = pthread_create(&pth, NULL, hello, NULL);
	if (ret != 0)
	{
		printf("pthread_create failed!\n");
		return -1;
	}

	sleep(1);
	printf("pth = %u\n", pth);
	printf("main pth = %u\n", pthread_self());
	printf("main : pid = %d\n", getpid());
	return 0;
}
