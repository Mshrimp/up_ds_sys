/***************************************************
	进程ID和线程ID测试：
***************************************************/

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


int main(int argc, char *argv[])
{
	unsigned int i = 10;

	printf("pid = %d, \n", getpid());	//打印进程ID
	printf("pthread = %lu\n", pthread_self());	//打印线程ID
	printf("pthread = %lu\n", pthread_self());
	printf("pthread = %lu\n", pthread_self());

	return 0;
}
