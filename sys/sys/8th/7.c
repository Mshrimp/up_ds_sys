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

int fd;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *write_file(void *data)
{
	int count = 1;
	char buf[128];

	/*sleep(1);*/
	pthread_mutex_lock(&mutex);
	while(1)
	{
		snprintf(buf, sizeof(buf), "%s : count = %d\n", (char *)data, count++);
		write(fd, buf, strlen(buf));
		if (count > 1000)
		{
			/*pthread_mutex_unlock(&mutex);*/
			/*break;*/
			return 0;
			/*pthread_exit(NULL);*/
		}
	}
	pthread_mutex_unlock(&mutex);
	//printf("data = %s\n", (char *)data);
	
	pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
	//两个线程同时操作一个文件
	pthread_t pth;
	//初始化锁
	/*pthread_mutex_init(&mutex, NULL);*/

	
	fd = open("./test", O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0)
	{
		perror("open");
		return -1;
	}
	//子线程
	pthread_create(&pth, NULL, write_file, "child");

	write_file("parent");


	

	/*sleep(1);*/
	//主线程
	/*pthread_join(pth, NULL);*/
	//销毁锁
	
	pthread_mutex_destroy(&mutex);
	return 0;
}
