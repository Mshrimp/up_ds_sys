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

void free_p(void *data)
{
	printf("free_p!\n");
	free(data);

}
void free_q(void *data)
{
	printf("free_q!\n");
}
void free_v(void *data)
{
	printf("free_v!\n");
}

int main(int argc, char *argv[])
{
	int *p = NULL, *q = NULL, *v = NULL;

	p = (int *)malloc(sizeof(p));
	if (p == NULL)
	{
		return -1;
	}
	*p = 1122;
	printf("main stat!\n");

	/*q = (int *)malloc(4);*/

	pthread_cleanup_push(free_p, p);	
	pthread_cleanup_push(free_q, NULL);	
	pthread_cleanup_push(free_v, NULL);	

	printf("*p = %d %p\n", *p, p);
	printf("hello!\n");
	pthread_cleanup_pop(2);
    /*
	 *q = (int *)malloc(4);
	 **q = 123;
     */
	pthread_cleanup_pop(3);
	pthread_cleanup_pop(4);
	printf("*p = %d %p\n", *p, p);

	// 1 1 1 p q v => v q p 
	// 0 1 1 p q v => q p
	printf("main end!\n");
	return 0;
}





