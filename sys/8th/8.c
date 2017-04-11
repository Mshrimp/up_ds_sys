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

void *func(void *data)
{
	printf("pthread  : %u data : %s\n", pthread_self(), (char *)data);
	pthread_exit(0);
}
int main(int argc, char *argv[])
{
	pthread_t pth[4];
	//创建1号线程
	
	pthread_create(&pth[0], NULL, func, "hello 111");
	/*sleep(1);*/
	//创建2号线程
	pthread_create(&pth[1], NULL, func, "hello 222");
	/*sleep(1);*/
	//创建3号线程
	pthread_create(&pth[2], NULL, func, "hello 333");
	/*sleep(1);*/
	//创建4号线程
	pthread_create(&pth[3], NULL, func, "hello 444");

	/*sleep(1);*/

	return 0;
}
