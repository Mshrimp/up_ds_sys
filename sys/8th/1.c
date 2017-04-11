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

//进程 线程
int main(int argc, char *argv[])
{
	unsigned
	int i = 10;
	printf("pid = %d\n", getpid());
	/*printf("i = %i\n", i);*/
	printf("pthread_self = %lu\n", pthread_self());
    /*
	 *printf("pthread_self = %d\n", pthread_self());
	 *printf("pthread_self = %u\n", pthread_self());
     */

	return 0;
}
