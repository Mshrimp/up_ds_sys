/*********************************************************************
	创建新线程测试：
		pthread_create(&pth, NULL, func, NULL);
		创建的新线程和主线程的进程号PID相同，线程号id不相同
	pthread库不是Linux系统默认的库，编译时候使用静态库libpthread.a:
		gcc test.c -o test -lpthread
*********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <time.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <glob.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/resource.h>
#include <pthread.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

void *hello(void *data)
{
	int i;
	int count = 1000;

	printf("hello!\n");
	printf("hello : pthread = %u\n", pthread_self());
	printf("hello : pid = %u\n", getpid());

	if (0 == fork())
	{
		count++;
		printf("child : pid = %d  pthread = %u  count = %d\n", getpid(), pthread_self(), count);
		exit(0);
	}

	wait(NULL);
	printf("parent : pid = %d  pthread = %u\n", getpid(), pthread_self());

}

int main(int argc, char *argv[])
{
	int ret = 0;
	pthread_t pth;

	printf("main begin!\n");
	printf("pth = %u\n", pthread_self());
	ret = pthread_create(&pth, NULL, hello, NULL);
	if (ret != 0)
	{
		printf("pthread_create failed!\n");
		return -1;
	}
	
	sleep(1);
	printf("pth = %u\n", pth);
	printf("main : pthread = %u\n", pthread_self());
	printf("main : pid = %u\n", getpid());

	printf("main end!\n");

	return 0;
}
