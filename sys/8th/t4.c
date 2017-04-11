/*********************************************************
    pthread_join()自动把线程置于分离状态，资源就可以恢复
        如果线程已经处于分离状态，该函数调用失败，返回EINVAL
    第二个参数设置为NULL，函数可以等待指定进程终止，
        但并不获取线程的终止状态。

*********************************************************/

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
