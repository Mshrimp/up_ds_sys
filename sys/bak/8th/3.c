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

#define MAX 1

void *func(void *data)
{
	printf("data = %d\n", *(int *)data);
	*(int *)data = 4321;
	printf("data = %d\n", *(int *)data);
	printf("hello!\n");
	
	if (fork() == 0)
	{
		/*printf("child : data = %d count = %d\n", *(int *)data, count);*/\
		exit(0);
	}
	else
	{
		wait(NULL);
		printf("parent : data = %d count = %d\n", *(int *)data, count);
	
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int i = 2;
	int count = 1234;
	pthread_t pth[MAX];

	for (i = 0; i < MAX; i++)
	{
		usleep(10000);
		pthread_create(pth + i, NULL, func, &count);
	}

	sleep(1);
	printf("main : count = %d\n", count);
	printf("main end!\n");

	return 0;
}
