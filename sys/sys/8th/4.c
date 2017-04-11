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

#define MAX 10

void *func(void *data)
{
	static int a = 12;
	printf("&a = %p\n", &a);
	sleep(1);
	printf("hello!\n");
	pthread_exit(&a);
	//exit(0);

	/*return &a;*/
}
int main(int argc, char *argv[])
{
	int i;
	int count = 123;
	pthread_t pth[MAX];
	int *p = NULL;

	for (i = 0;i < MAX; i++)
	{
		pthread_create(pth + i, NULL, func, &count);
	}

	/*sleep(1);*/

	for (i = 0; i < MAX; i++)
	{
		pthread_join(pth[i], (void **)&p);
		printf("*p = %d\n", *p);
	}
	printf("count = %d\n", count);
	return 0;
}
